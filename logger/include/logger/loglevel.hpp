#pragma once
#include <string>

namespace logger {

/**
 * @brief Severity levels supported by the logger.
 *
 * Levels are ordered from least severe to most severe. This ordering is used by
 * Logger to filter messages below the configured minimum level.
 */
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

/**
 * @brief Convert a string to a log level.
 *
 * @param level Textual level name.
 * @return Matching LogLevel value, or INFO when the string is not recognized.
 */
LogLevel logLevelFromString(const std::string &level);

/**
 * @brief Convert a log level to string.
 *
 * @param level LogLevel value.
 * @return Uppercase name.
 */
std::string logLevelToString(LogLevel level);

} // namespace logger
