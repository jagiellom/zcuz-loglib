#include "logger/logger.hpp"

#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace logger {

void Logger::registerSink(std::shared_ptr<LogSink> sink) {
  sinks.push_back(std::move(sink));
}

void Logger::logTrace(const std::string &module, const std::string &message) {
  log(LogLevel::TRACE, module, message);
}

void Logger::logDebug(const std::string &module, const std::string &message) {
  log(LogLevel::DEBUG, module, message);
}

void Logger::logInfo(const std::string &module, const std::string &message) {
  log(LogLevel::INFO, module, message);
}

void Logger::logWarn(const std::string &module, const std::string &message) {
  log(LogLevel::WARN, module, message);
}

void Logger::logError(const std::string &module, const std::string &message) {
  log(LogLevel::ERROR, module, message);
}

void Logger::log(LogLevel level, const std::string &module,
                 const std::string &msg) {
  LogEntry log_info;

  log_info.timestamp = std::chrono::system_clock::now();
  log_info.level = level;
  log_info.module = module;
  log_info.msg = msg;
  log_info.thread_id = std::this_thread::get_id();

  for (auto &sink : sinks) {
    sink->log(log_info);
  }
}

} // namespace logger
