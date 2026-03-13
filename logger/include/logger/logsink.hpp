#pragma once

#include "logentry.hpp"
#include <memory>
#include <vector>

namespace logger {

/**
 * @brief Abstract class defining base LogSink behavior
 */
class LogSink {
public:
  virtual ~LogSink() = default;
  virtual void log(const LogEntry &msg) = 0;
};
} // namespace logger
