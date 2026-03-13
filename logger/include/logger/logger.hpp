#pragma once

#include "logsink.hpp"
#include <memory>

namespace logger {
/**
 * @brief Base logger class
 * Main feature and responsibility of logger class is to accept log entries
 * and output these entries to specified sinks (eg. file, console or network)
 * Can work in both synchronous and asynchronous modes
 */
class Logger {
public:
  void registerSink(std::shared_ptr<LogSink> sink);
};
} // namespace logger
