#include "logger/jsonformatter.hpp"

#include "logger/loglevel.hpp"

#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>

namespace logger {

std::string threadIdToString(const std::thread::id &thread_id) {
  std::stringstream stream;
  stream << thread_id;

  return stream.str();
}

std::string JsonFormatter::format(const LogEntry &entry) {
  nlohmann::json json;

  json["timestamp"] = formatTimestamp(entry.timestamp);
  json["level"] = logLevelToString(entry.level);
  json["module"] = entry.module;
  json["message"] = entry.msg;
  json["thread_id"] = threadIdToString(entry.thread_id);

  return json.dump();
}

} // namespace logger
