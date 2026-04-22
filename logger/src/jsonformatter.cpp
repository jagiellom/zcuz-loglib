#include "logger/jsonformatter.hpp"

#include "logger/loglevel.hpp"

#include <nlohmann/json.hpp>

namespace logger {

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
