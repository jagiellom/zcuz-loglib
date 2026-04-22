#pragma once

#include "logger/logformatter.hpp"

namespace logger {

/**
 * @brief Formatter that produces simple log line.
 *
 * output format :
 * [LEVEL] [YYYY-MM-DD-HH:MM:SS] [module] message
 */
class SimpleTextFormatter : public LogFormatter {
public:
  /**
   * @brief Format a log entry as text line.
   *
   * @param entry LogEntry to format.
   * @return Log string.
   */
  std::string format(const LogEntry &entry) override;
};

} // namespace logger
