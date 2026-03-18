#include "logger/filesink.hpp"
#include "logger/logger.hpp"
#include <chrono>
#include <memory>
#include <thread>

int main() {
  logger::Logger logger;

  logger.setMinLevel(logger::LogLevel::TRACE);

  logger.registerSink(std::make_shared<logger::FileSink>("./logs/", 1000));

  logger.logDebug("main", "App started from logger");

  for (int i = 0; i < 400; ++i) {
    logger.logWarn("main", "Test rotate");
    std::this_thread::sleep_for(std::chrono::milliseconds(1001));
  }
  return 0;
}
