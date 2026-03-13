#pragma once
#include <chrono>
#include <string>
#include <thread>

namespace logger {

enum class LogLevel {
  /// Detailed diagnostic information
  TRACE,
  /// Debugging information used mostly during development
  DEBUG,
  /// Informational messages during system operation
  INFO,
  /// Warning for possible problems
  WARN,
  /// Error information indicating failure
  ERROR,
};

/**
 * @brief Representation of singular log entry.
 */
struct LogEntry {
  /// Timestamp of log entry
  std::chrono::system_clock::time_point timestamp;
  /// Level of log entry
  LogLevel level;
  /// Module that produced the log entry
  std::string module;
  /// Log message
  std::string msg;
  /// Id of running thread that produced log entry
  std::thread::id thread_id;
};

} // namespace logger
