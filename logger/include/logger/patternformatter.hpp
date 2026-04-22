#pragma once

#include "logger/logformatter.hpp"
#include "logger/token.hpp"
#include <string>
#include <vector>

namespace logger {

/**
 * @brief Formatter that builds log messages from a user-defined pattern.
 *
 * PatternFormatter parses a pattern into tokens once during construction and
 * later uses those tokens to format each LogEntry. Supported fields are
 * represented by TokenType values, while all other text is kept as custom text.
 */
class PatternFormatter : public LogFormatter {
public:
  /**
   * @brief Create a formatter from a pattern string.
   *
   * @param pattern Pattern containing text and placeholders such as
   * {timestamp}, {level}, {module}, and {message}.
   */
  explicit PatternFormatter(const std::string &pattern);

  /**
   * @brief Format a log entry using the parsed pattern.
   *
   * @param entry Log entry to format.
   * @return Formatted log message.
   */
  std::string format(const LogEntry &entry) override;

private:
  /**
   * @brief Parse pattern text into formatter tokens.
   *
   * @param pattern Pattern string passed to the constructor.
   */
  void parsePattern(const std::string &pattern);

  /**
   * @brief Ordered list of parsed tokens used during formatting.
   */
  std::vector<Token> tokens_;
};
} // namespace logger
