#include "logger/csvformatter.hpp"

#include "logger/loglevel.hpp"

#include <sstream>
#include <string>
#include <thread>

namespace logger {

std::string threadIdToString(const std::thread::id &thread_id) {
  std::stringstream stream;
  stream << thread_id;

  return stream.str();
}

std::string escapeCsvField(const std::string &field) {
  bool needs_quotes = false;
  std::string escaped;
  escaped.reserve(field.size());

  for (char c : field) {
    if (c == '"') {
      escaped += "\"\"";
      needs_quotes = true;
    } else {
      escaped += c;
    }

    if (c == ',' || c == '\n' || c == '\r') {
      needs_quotes = true;
    }
  }

  if (!needs_quotes) {
    return escaped;
  }

  return '"' + escaped + '"';
}

std::string CsvFormatter::format(const LogEntry &entry) {
  std::stringstream stream;

  stream << escapeCsvField(formatTimestamp(entry.timestamp)) << ','
         << escapeCsvField(logLevelToString(entry.level)) << ','
         << escapeCsvField(entry.module) << ',' << escapeCsvField(entry.msg)
         << ',' << escapeCsvField(threadIdToString(entry.thread_id));

  return stream.str();
}

} // namespace logger
