#include "logger/consolesink.hpp"
#include <iostream>
#include <memory>
#include <mutex>
#include <utility>

namespace logger {

ConsoleSink::ConsoleSink() = default;

ConsoleSink::ConsoleSink(std::shared_ptr<LogFormatter> formatter)
    : LogSink(std::move(formatter)) {}

void ConsoleSink::log(const LogEntry &entry) {
  std::lock_guard<std::mutex> lock(mut);
  std::cout << format(entry) << std::endl;
}

} // namespace logger
