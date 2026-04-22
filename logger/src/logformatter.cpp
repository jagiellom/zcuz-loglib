#include "logger/logformatter.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace logger {

std::string LogFormatter::formatTimestamp(
    const std::chrono::system_clock::time_point &time_point) const {
  auto time = std::chrono::system_clock::to_time_t(time_point);
  auto tm_ptr = std::localtime(&time);
  auto tm = *tm_ptr;

  std::stringstream stream;
  stream << std::put_time(&tm, "%Y-%m-%d-%H:%M:%S");

  return stream.str();
}

} // namespace logger
