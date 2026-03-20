#include "logger/networksink.hpp"
#include "logger/loglevel.hpp"
#include <chrono>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>

namespace logger {

NetworkSink::NetworkSink(const std::string &host, int port)
    : host_(host), port_(port), socket_(io_context_) {

  try {
    connect();
  } catch (const std::exception &e) {
    std::cerr << "[NetworkSink ERROR] - cannot connect to tcp socket."
              << std::endl;
  }

  retry_thread_ = std::thread(&NetworkSink::retryLoop, this);
}

NetworkSink::~NetworkSink() {
  running_ = false;

  if (retry_thread_.joinable()) {
    retry_thread_.join();
  }

  std::lock_guard<std::mutex> lock(mut_);
  flushBuffer();
}

void NetworkSink::connect() {
  asio::ip::tcp::resolver resolver(io_context_);
  auto endpoints = resolver.resolve(host_, std::to_string(port_));

  asio::connect(socket_, endpoints);
}

bool NetworkSink::send(const std::string &data) {
  try {
    asio::write(socket_, asio::buffer(data));
    return true;
  } catch (...) {
    return false;
  }
}

std::string NetworkSink::serialize(const LogEntry &entry) {
  nlohmann::json j;

  j["level"] = logLevelToString(entry.level);
  j["message"] = entry.msg;
  j["module"] = entry.module;
  j["timestmap"] = getTimestamp(std::chrono::system_clock::now());

  // using \n as end of frame
  return j.dump() + "\n";
}

void NetworkSink::flushBuffer() {
  while (!buffer_.empty()) {
    auto &entry = buffer_.front();

    if (send(serialize(entry))) {
      buffer_.pop();
      backoff_ = 100;
    } else {
      socket_.close();
      try {
        connect();
      } catch (const std::exception &e) {
        std::cerr << "[NetworkSink ERROR] - cannot connect to tcp socket."
                  << std::endl;
      } catch (...) {
        std::cerr << "[NetworkSink ERROR] - unknown exception." << std::endl;
      }
      break;
    }
  }
}

void NetworkSink::retryLoop() {
  while (running_) {
    {
      std::lock_guard<std::mutex> lock(mut_);
      flushBuffer();
    } // scope mutex outside sleep

    std::this_thread::sleep_for(std::chrono::milliseconds(backoff_));

    backoff_ = std::min(backoff_ * 2, max_backoff_);
  }
}

void NetworkSink::log(const LogEntry &entry) {

  std::lock_guard<std::mutex> lock(mut_);
  auto data = serialize(entry);

  if (send(data))
    return;

  // failed send() - realizing that networklogging is a bad idea here. Where do
  // I log errors with logger now??
  socket_.close();
  try {
    connect();
  } catch (const std::exception &e) {
    std::cerr << "[NetworkSink ERROR] - cannot connect to tcp socket."
              << std::endl;
  } catch (...) {
    std::cerr << "[NetworkSink ERROR] - unknown exception." << std::endl;
  }

  // remove oldest entries if buffer is too big
  if (buffer_.size() + 1 > max_buffer_size_) {
    buffer_.pop();
  }

  // add entry that failed to send to retry buffer
  buffer_.push(entry);
}

} // namespace logger
