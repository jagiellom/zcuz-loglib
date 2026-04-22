#include "logger/patternformatter.hpp"

#include "logger/loglevel.hpp"
#include "logger/token.hpp"

#include <sstream>

namespace logger {
namespace {

const char *TIMESTAMP = "timestamp";
const char *LEVEL = "level";
const char *MODULE = "module";
const char *MESSAGE = "message";

} // namespace

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
      if (end == std::string::npos) {
        buffer += pattern.substr(i);
        break;
      }

      auto key = pattern.substr(i + 1, end - i - 1);

      if (key == TIMESTAMP)
        tokens_.push_back({TokenType::TIMESTAMP, ""});
      else if (key == LEVEL)
        tokens_.push_back({TokenType::LEVEL, ""});
      else if (key == MODULE)
        tokens_.push_back({TokenType::MODULE, ""});
      else if (key == MESSAGE)
        tokens_.push_back({TokenType::MESSAGE, ""});
      else
        tokens_.push_back(
            {TokenType::CUSTOM_TEXT, pattern.substr(i, end - i + 1)});

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

std::string PatternFormatter::format(const LogEntry &entry) {
  std::stringstream stream;

  for (const auto &token : tokens_) {
    switch (token.type) {
    case TokenType::TIMESTAMP:
      stream << formatTimestamp(entry.timestamp);
      break;
    case TokenType::LEVEL:
      stream << logLevelToString(entry.level);
      break;
    case TokenType::MODULE:
      stream << entry.module;
      break;
    case TokenType::MESSAGE:
      stream << entry.msg;
      break;
    case TokenType::CUSTOM_TEXT:
      stream << token.text;
      break;
    }
  }

  return stream.str();
}

} // namespace logger
