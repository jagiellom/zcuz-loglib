#pragma once

#include "logger/logformatter.hpp"

namespace logger {

/**
 * @brief Formatter that outputs log entries as CSV rows.
 */
class CsvFormatter : public LogFormatter {
public:
  /**
   * @brief Format a log entry as a CSV row.
   *
   * @param entry Log entry to format.
   * @return CSV row.
   */
  std::string format(const LogEntry &entry) override;
};

} // namespace logger
