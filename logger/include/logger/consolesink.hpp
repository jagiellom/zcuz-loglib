#pragma once

#include "logger/logentry.hpp"
#include "logsink.hpp"
#include <memory>
#include <mutex>

namespace logger {
/**
 * @brief Sink outputting log entries to console
 *
 * Outputs to stdout
 */
class ConsoleSink : public LogSink {
public:
  /**
   * @brief Create a ConsoleSink using the default text formatter.
   */
  ConsoleSink();

  /**
   * @brief Create a ConsoleSink using a custom formatter.
   *
   * @param formatter Formatter used to convert log entries to strings.
   */
  explicit ConsoleSink(std::shared_ptr<LogFormatter> formatter);

  /**
   * @brief Outputs log entry to stdout.
   *
   * @param entry Log entry to write.
   */
  void log(const LogEntry &entry) override;

private:
  /**
   * @brief Mutex for console output as its not threadsafe.
   */
  std::mutex mut;
};
} // namespace logger
