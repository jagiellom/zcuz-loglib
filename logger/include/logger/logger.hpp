#pragma once

#include "logsink.hpp"
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
  /**
   * @brief Register sink within logger
   *
   * @param sink Output destination for logged data
   */
  void registerSink(std::shared_ptr<LogSink> sink);

  /**
   * @brief Log with TRACE serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void logTrace(const std::string &module, const std::string &msg);
  /**
   * @brief Log with DEBUG serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void logDebug(const std::string &module, const std::string &msg);
  /**
   * @brief Log with INFO serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void logInfo(const std::string &module, const std::string &msg);
  /**
   * @brief Log with WARN serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void logWarn(const std::string &module, const std::string &msg);
  /**
   * @brief Log with ERROR serverity level
   *
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void logError(const std::string &module, const std::string &msg);

private:
  /**
   * @brief Logs message with set severity level
   *
   * @param level Severity level
   * @param module Source of log message - ie module
   * @param msg Text message
   */
  void log(LogLevel level, const std::string &module, const std::string &msg);
  std::vector<std::shared_ptr<LogSink>> sinks;
};
} // namespace logger
