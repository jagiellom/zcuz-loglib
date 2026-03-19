#pragma once

#include "logsink.hpp"
#include "threadsafequeue.hpp"
#include <memory>
#include <string>

namespace logger {
/**
 * @brief Base logger class
 * Main feature and responsibility of logger class is to accept log entries
 * and output these entries to specified sinks (eg. file, console or network)
 * Can work in both synchronous and asynchronous modes
 */
class Logger {
public:
  Logger();
  ~Logger();

  // Can't copy threads
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  // Can't move atomics
  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

  /**
   * @brief Register sink within logger
   *
   * @param sink Output destination for logged data
   */
  void register_sink(std::shared_ptr<LogSink> sink);

  /**
   * @brief Set minimal severity level that will be logged
   * All levels below set level will be skipped, useful for debug/release modes
   * Defaults to INFO
   *
   * @param level Minimum level of severity to be logged
   */
  void set_min_level(LogLevel level);

  /**
   * @brief Log with TRACE serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void trace(const std::string &module, const std::string &msg);
  /**
   * @brief Log with DEBUG serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void debug(const std::string &module, const std::string &msg);
  /**
   * @brief Log with INFO serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void info(const std::string &module, const std::string &msg);
  /**
   * @brief Log with WARN serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void warn(const std::string &module, const std::string &msg);
  /**
   * @brief Log with ERROR serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void error(const std::string &module, const std::string &msg);

private:
  /**
   * @brief Logs message with set severity level
   *
   * @param level Severity level
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void log(LogLevel level, const std::string &module, const std::string &msg);

  /**
   * @brief Method that dispatches logging to sinks in worker thread
   */
  void dispatch_logs();

  /**
   * @brief Vector of available sinks
   *
   * Sinks are used to transfer data to their desired output (like file,
   * console, socket etc.)
   */
  std::vector<std::shared_ptr<LogSink>> sinks_;

  /**
   * @brief Minimal level of logged entries.
   *
   * Logs with lower severity lever than set in minLevel will be discarded
   */
  LogLevel min_level_ = LogLevel::INFO;

  /**
   * @brief Worker thread used to dispatch entries to sinks
   */
  std::thread worker_;

  /**
   * @brief Queue of log entries
   */
  ThreadSafeQueue<LogEntry> queue_;

  /**
   * @brief Thread safe information whether logger thread is running
   */
  std::atomic<bool> is_running_{false};
};
} // namespace logger
