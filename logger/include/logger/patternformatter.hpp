#pragma once

#include "logger/logformatter.hpp"
#include "logger/token.hpp"

namespace logger {
class PatternFormatter : public LogFormatter {
public:
  explicit PatternFormatter(const std::string &pattern);
  std::string format(const LogEntry &entry) override;

private:
  void parsePattern(const std::string &pattern);

  std::vector<Token> tokens_;
};
} // namespace logger
