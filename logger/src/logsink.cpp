#include "logger/logsink.hpp"
#include "logger/simpletextformatter.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace logger {

LogSink::LogSink() : LogSink(std::make_shared<SimpleTextFormatter>()) {}

LogSink::LogSink(std::shared_ptr<LogFormatter> formatter)
    : formatter_(std::move(formatter)) {
  if (!formatter_) {
    throw std::invalid_argument("LogSink formatter cannot be null");
  }
}

std::string
LogSink::getTimestamp(const std::chrono::system_clock::time_point &time_point) {
  auto time = std::chrono::system_clock::to_time_t(time_point);
  auto tm_ptr = std::localtime(&time);
  auto tm = *tm_ptr;
  std::stringstream stream;
  stream << std::put_time(&tm, "%Y-%m-%d-%H:%M:%S");

  return stream.str();
};

std::string LogSink::format(const LogEntry &entry) const {
  return formatter_->format(entry);
}

} // namespace logger
