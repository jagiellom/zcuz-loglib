#pragma once

#include "logger/logsink.hpp"
#include <asio.hpp>
#include <mutex>
#include <queue>
#include <string>

namespace logger {

/**
 * @brief Sink responsible for outputting log entries through tcp
 */
class NetworkSink : public LogSink {
public:
  /**
   * @brief Constructor
   *
   * @param host Hostname of tcp socket
   * @param port Port of tcp socket
   */
  NetworkSink(const std::string &host, int port);
  ~NetworkSink();

  /**
   * @brief Outputs log entry through tcp
   */
  void log(const LogEntry &entry) override;

private:
  /**
   * @brief Connects to tcp socket defined by host_ and port_
   */
  void connect();
  /**
   * @brief Sends serialized data through tcp socket. Single frame consists of
   * json line ending with \n.
   */
  bool send(const std::string &data);
  /**
   * @brief Serializes LogEntry to json.
   */
  std::string serialize(const LogEntry &entry);

  /**
   * @brief Retry handling loop function.
   */
  void retryLoop();
  /**
   * @brief Flushes retry buffer containing messages that failed to be sent.
   */
  void flushBuffer();

  /**
   * @brief Retry buffer holding entries that failed to be sent.
   */
  std::queue<LogEntry> buffer_;
  /**
   * @brief Maximum size of retry buffer. Will drop oldest messages when full.
   */
  const std::size_t max_buffer_size_ = 3;
  /**
   * @brief Additional thread that runs retry loop.
   */
  std::thread retry_thread_;
  /**
   * @brief Atomic bool that specifies whether retry thread is running.
   */
  std::atomic<bool> running_{true};
  /**
   * @brief Backoff in ms. Will grow on every failure up to max_backoff_.
   */
  int backoff_ = 100;
  /**
   * @brief Maximum backoff in ms.
   */
  const int max_backoff_ = 3000;
  std::mutex mut_;
  /**
   * @brief Hostname of tcp socket.
   */
  std::string host_;
  /**
   * @brief Port of tcp socket.
   */
  int port_;
  asio::io_context io_context_;
  asio::ip::tcp::socket socket_;
};

} // namespace logger
