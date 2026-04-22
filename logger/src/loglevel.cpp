#include "logger/loglevel.hpp"
#include <string>
namespace logger {

LogLevel logLevelFromString(const std::string &str) {
  if (str == "trace")
    return LogLevel::TRACE;
  if (str == "debug")
    return LogLevel::DEBUG;
  if (str == "info")
    return LogLevel::INFO;
  if (str == "warn")
    return LogLevel::WARN;
  if (str == "error")
    return LogLevel::ERROR;

  return LogLevel::INFO;
};

std::string logLevelToString(LogLevel level) {
  switch (level) {
  case LogLevel::TRACE:
    return "TRACE";
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARN:
    return "WARN";
  case LogLevel::ERROR:
    return "ERROR";
    break;
  }
  return "";
};

} // namespace logger
