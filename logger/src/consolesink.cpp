#include "logger/consolesink.hpp"
#include "logger/logentry.hpp"
#include "logger/loglevel.hpp"
#include <ctime>
#include <iostream>
#include <mutex>

namespace logger {
void ConsoleSink::log(const LogEntry &entry) {
  std::lock_guard<std::mutex> lock(mut);
  std::cout << "[" << logLevelToString(entry.level) << "] "
            << "[" << getTimestamp(entry.timestamp) << "] "
            << "[" << entry.module << "] " << entry.msg << std::endl;
}

} // namespace logger
