#pragma once

#include "logformatter.hpp"
#include "logentry.hpp"
#include <chrono>
#include <memory>
#include <string>

namespace logger {

/**
 * @brief Abstract class defining base LogSink behavior
 */
class LogSink {
public:
  /**
   * @brief Create a sink with the default text formatter.
   */
  LogSink();

  /**
   * @brief Create a sink with a custom formatter.
   *
   * @param formatter Formatter used to convert log entries to strings.
   */
  explicit LogSink(std::shared_ptr<LogFormatter> formatter);

  /**
   * @brief Default virtual destructor for sink implementations.
   */
  virtual ~LogSink() = default;

  /**
   * @brief Write a log entry to the sink destination.
   *
   * @param entry Log entry to write.
   */
  virtual void log(const LogEntry &entry) = 0;

  /**
   * @brief Format a time point as a timestamp string.
   *
   * @param time_point Time point to convert.
   * @return Timestamp formatted as YYYY-MM-DD-HH:MM:SS.
   */
  std::string
  getTimestamp(const std::chrono::system_clock::time_point &time_point);

protected:
  /**
   * @brief Format a log entry using this sink's formatter.
   *
   * @param entry Log entry to format.
   * @return Formatted log entry.
   */
  std::string format(const LogEntry &entry) const;

private:
  /**
   * @brief Formatter used by the sink.
   */
  std::shared_ptr<LogFormatter> formatter_;
};
} // namespace logger
