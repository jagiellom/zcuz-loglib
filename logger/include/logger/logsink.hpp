#pragma once

#include "logentry.hpp"
#include <chrono>
#include <string>

namespace logger {

/**
 * @brief Abstract class defining base LogSink behavior
 */
class LogSink {
public:
  virtual ~LogSink() = default;
  virtual void log(const LogEntry &entry) = 0;

  std::string
  getTimestamp(const std::chrono::system_clock::time_point &time_point);
};
} // namespace logger
