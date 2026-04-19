#pragma once

#include <string>

namespace logger {
enum class TokenType { TIMESTAMP, LEVEL, MESSAGE, MODULE, CUSTOM_TEXT };

struct Token {
  TokenType type;
  std::string text;
};

} // namespace logger
