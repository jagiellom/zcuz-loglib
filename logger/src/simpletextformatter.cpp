#include "logger/simpletextformatter.hpp"

#include "logger/loglevel.hpp"

#include <sstream>

namespace logger {

std::string SimpleTextFormatter::format(const LogEntry &entry) {
  std::stringstream stream;

  stream << "[" << logLevelToString(entry.level) << "] "
         << "[" << formatTimestamp(entry.timestamp) << "] "
         << "[" << entry.module << "] " << entry.msg;

  return stream.str();
}

} // namespace logger
