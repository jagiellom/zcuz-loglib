#include "logger/logsink.hpp"
namespace logger {

std::string
LogSink::getTimestamp(const std::chrono::system_clock::time_point &time_point) {
  auto time = std::chrono::system_clock::to_time_t(time_point);
  auto tm_ptr = std::localtime(&time);
  auto tm = *tm_ptr;
  std::stringstream stream;
  stream << std::put_time(&tm, "%H:%M:%S %Y-%m-%d");

  return stream.str();
};

} // namespace logger
