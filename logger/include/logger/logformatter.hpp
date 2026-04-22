#pragma once

#include "logger/logentry.hpp"
#include <chrono>
#include <string>

namespace logger {

/**
 * @brief Interface for classes that convert log entries into strings.
 *
 * Formatters separate log entry from sink that writes it.
 * Implementations can produce simple text, text based on patterns, JSON or CSV.
 */
class LogFormatter {
public:
  /**
   * @brief Default virtual destructor for formatter implementations.
   */
  virtual ~LogFormatter() = default;

  /**
   * @brief Format a log entry to a string.
   *
   * @param entry Log entry to format.
   * @return Log entry as string.
   */
  virtual std::string format(const LogEntry &entry) = 0;

protected:
  /**
   * @brief Format a timestamp for log formatter output.
   *
   * @param time_point Time point to format.
   * @return Timestamp stirng.
   */
  std::string formatTimestamp(
      const std::chrono::system_clock::time_point &time_point) const;
};
} // namespace logger
