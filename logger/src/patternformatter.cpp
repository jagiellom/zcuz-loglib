#include "logger/patternformatter.hpp"
#include "logger/token.hpp"

namespace logger {

const std::string TIMESTAMP = "timestamp";
const std::string LEVEL = "level";
const std::string MODULE = "module";
const std::string MESSAGE = "message";

void PatternFormatter::parsePattern(const std::string &pattern) {
  // We need buffer to store values that do not match the pattern. This is used
  // in custom text.
  std::string buffer;
  for (size_t i = 0; i < pattern.size(); ++i) {
    if (pattern[i] == '{') {
      if (!buffer.empty()) {
        tokens_.push_back({TokenType::CUSTOM_TEXT, buffer});
        buffer.clear();
      }

      auto end = pattern.find('}', i);
      auto key = pattern.substr(i + 1, end - i - 1);

      if (key == TIMESTAMP)
        tokens_.push_back({TokenType::TIMESTAMP, ""});
      else if (key == LEVEL)
        tokens_.push_back({TokenType::LEVEL, ""});
      else if (key == MODULE)
        tokens_.push_back({TokenType::MODULE, ""});
      else if (key == MESSAGE)
        tokens_.push_back({TokenType::MESSAGE, ""});

      i = end;
    } else {
      buffer += pattern[i];
    }
  }

  if (!buffer.empty()) {
    tokens_.push_back({TokenType::CUSTOM_TEXT, buffer});
  }
};

PatternFormatter::PatternFormatter(const std::string &pattern) {
  parsePattern(pattern);
}

} // namespace logger
