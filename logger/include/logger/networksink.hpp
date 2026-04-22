#pragma once

#include "logger/logsink.hpp"
#include <asio.hpp>
#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

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

  /**
   * @brief Create a NetworkSink using a custom formatter.
   *
   * @param host Hostname of tcp socket.
   * @param port Port of tcp socket.
   * @param formatter Formatter used to serialize log entries.
   */
  NetworkSink(const std::string &host, int port,
              std::shared_ptr<LogFormatter> formatter);

  /**
   * @brief Stop retry handling and flush buffered entries.
   */
  ~NetworkSink();

  /**
   * @brief Outputs log entry through tcp
   *
   * @param entry Log entry to send.
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
   *
   * @param data Serialized frame to send.
   * @return true when the frame was sent, false when sending failed.
   */
  bool send(const std::string &data);

  /**
   * @brief Serializes LogEntry to json.
   *
   * @param entry Log entry to serialize.
   * @return JSON line terminated with a newline character.
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

  /**
   * @brief Mutex protecting socket access and retry buffer state.
   */
  std::mutex mut_;

  /**
   * @brief Hostname of tcp socket.
   */
  std::string host_;
  /**
   * @brief Port of tcp socket.
   */
  int port_;

  /**
   * @brief ASIO context used by the TCP socket and resolver.
   */
  asio::io_context io_context_;

  /**
   * @brief TCP socket used to send serialized log entries.
   */
  asio::ip::tcp::socket socket_;
};

} // namespace logger
