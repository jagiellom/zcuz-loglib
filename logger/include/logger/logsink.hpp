#pragma once

#include "logmessage.hpp"

namespace logger {

/**
 * @brief Abstract class defining base LogSink behavior
 */
class LogSink {
public:
  virtual ~LogSink() = default;
  virtual void log(const LogMessage &msg) = 0;
};
} // namespace logger
