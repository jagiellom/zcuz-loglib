#pragma once

#include "logger/logentry.hpp"
#include "logsink.hpp"

namespace logger {
/**
 * @brief Sink responsible for outputting log entries to console
 *
 * Outputs to stdout
 */
class ConsoleSink : public LogSink {
public:
  /**
   * @brief Outputs log entry to stdout.
   */
  void log(const LogEntry &entry) override;

private:
  std::mutex mut;
};
} // namespace logger
