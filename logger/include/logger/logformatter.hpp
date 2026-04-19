#pragma once

#include "logger/logentry.hpp"
#include <string>

namespace logger {

class LogFormatter {
public:
  virtual ~LogFormatter() = default;

  virtual std::string format(const LogEntry &entry) = 0;
};
} // namespace logger
