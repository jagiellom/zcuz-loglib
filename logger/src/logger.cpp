#include "logger/logger.hpp"

#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace logger {

Logger::Logger()
    : worker_(std::thread(&Logger::dispatch_logs, this)), is_running_(true) {};

Logger::~Logger() {
  queue_.close();
  if (worker_.joinable()) {
    worker_.join();
  }
}

void Logger::register_sink(std::shared_ptr<LogSink> sink) {
  sinks_.push_back(std::move(sink));
}

void Logger::set_min_level(LogLevel level) { min_level_ = level; }

void Logger::trace(const std::string &module, const std::string &message) {
  log(LogLevel::TRACE, module, message);
}

void Logger::debug(const std::string &module, const std::string &message) {
  log(LogLevel::DEBUG, module, message);
}

void Logger::info(const std::string &module, const std::string &message) {
  log(LogLevel::INFO, module, message);
}

void Logger::warn(const std::string &module, const std::string &message) {
  log(LogLevel::WARN, module, message);
}

void Logger::error(const std::string &module, const std::string &message) {
  log(LogLevel::ERROR, module, message);
}

void Logger::log(LogLevel level, const std::string &module,
                 const std::string &msg) {

  if (level < min_level_) {
    return;
  }

  LogEntry entry;

  entry.timestamp = std::chrono::system_clock::now();
  entry.level = level;
  entry.module = module;
  entry.msg = msg;
  entry.thread_id = std::this_thread::get_id();

  for (auto &sink : sinks_) {
    sink->log(entry);
  }
}

void Logger::dispatch_logs() {

  LogEntry entry;

  while (queue_.try_pop(entry)) {
    for (auto &sink : sinks_) {
      sink->log(entry);
    }
  }
}

} // namespace logger
