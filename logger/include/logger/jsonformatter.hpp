#pragma once

#include "logger/logformatter.hpp"

namespace logger {

/**
 * @brief Formatter that outputs log entries as JSON.
 */
class JsonFormatter : public LogFormatter {
public:
  /**
   * @brief Format a log entry as a JSON object.
   *
   * @param entry Log entry to format.
   * @return Serialized JSON object.
   */
  std::string format(const LogEntry &entry) override;
};

} // namespace logger
