#pragma once
#include <string>

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

LogLevel logLevelFromString(const std::string &level);
std::string logLevelToString(LogLevel level);

} // namespace logger
