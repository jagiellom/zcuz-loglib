#pragma once

#include <string>

namespace logger {

/**
 * @brief Types of tokens supported by PatternFormatter.
 */
enum class TokenType { TIMESTAMP, LEVEL, MESSAGE, MODULE, CUSTOM_TEXT };

/**
 * @brief Single parsed element of a formatter pattern.
 *
 * A token either represents a dynamic LogEntry field, such as level or message,
 * or literal custom text that should be copied into the formatted output.
 */
struct Token {
  /**
   * @brief Kind of pattern token.
   */
  TokenType type;

  /**
   * @brief Literal text stored for CUSTOM_TEXT tokens.
   */
  std::string text;
};

} // namespace logger
