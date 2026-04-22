#include "logger/consolesink.hpp"
#include "logger/csvformatter.hpp"
#include "logger/filesink.hpp"
#include "logger/jsonformatter.hpp"
#include "logger/logger.hpp"
#include "logger/networksink.hpp"
#include "logger/patternformatter.hpp"

#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace testapp {

[[maybe_unused]] void runConsoleExample() {
  logger::Logger log;

  auto formatter = std::make_shared<logger::PatternFormatter>(
      "[{timestamp}] {level} {module}: {message}");
  log.register_sink(std::make_shared<logger::ConsoleSink>(formatter));

  log.set_min_level(logger::LogLevel::DEBUG);

  log.trace("Module A", "msg A 1");
  log.debug("Module A", "msg A 2");
  log.info("Module B", "msg B 1");
  log.warn("Module B", "msg B 2");
  log.error("Module C", "msg C 1");
}

[[maybe_unused]] void runCsvExample() {
  logger::Logger log;

  log.register_sink(std::make_shared<logger::FileSink>(
      "logs/csv-", 4096, std::make_shared<logger::CsvFormatter>()));

  log.info("module a", "csv \"example\" A 1");
  log.warn("Module A", "csv example A 2");
  log.error("Module B", "csv example B 1");
}

[[maybe_unused]] void runFileRotationExample() {
  logger::Logger log;

  auto text_formatter = std::make_shared<logger::PatternFormatter>(
      "{timestamp} | {level} | {module} | {message}");
  log.register_sink(std::make_shared<logger::FileSink>("logs/rotation-text-",
                                                       128, text_formatter));

  log.register_sink(std::make_shared<logger::FileSink>(
      "logs/rotation-json-", 128, std::make_shared<logger::JsonFormatter>()));

  for (int i = 1; i <= 150; ++i) {
    log.info("rotation", "rotation log test number:" + std::to_string(i));
  }
}

[[maybe_unused]] void runMultiSinkExample() {
  logger::Logger log;

  auto compact_formatter = std::make_shared<logger::PatternFormatter>(
      "{level} [{module}] {message}");

  log.register_sink(std::make_shared<logger::ConsoleSink>(compact_formatter));
  log.register_sink(std::make_shared<logger::FileSink>("logs/multi-sink-", 4096,
                                                       compact_formatter));

  log.set_min_level(logger::LogLevel::TRACE);

  log.trace("Module A", "msg A 1");
  log.debug("Module A", "msg A 2");
  log.info("Module B", "msg B 1");
  log.warn("Module B", "msg B 2");
  log.error("Module C", "msg C 1");
}

[[maybe_unused]] void runNetworkExample() {
  logger::Logger log;

  log.register_sink(std::make_shared<logger::NetworkSink>(
      "localhost", 9000, std::make_shared<logger::JsonFormatter>()));

  log.info("module A", "tcp msg 1");
  log.warn("Module A", "tcp msg 2");
  log.error("Module A", "tcp msg 3");

  std::this_thread::sleep_for(std::chrono::milliseconds(250));
}

} // namespace testapp

int main() {
  // testapp::runFileRotationExample();

  // testapp::runConsoleExample();
  // testapp::runCsvExample();
  // testapp::runMultiSinkExample();
  testapp::runNetworkExample();

  return 0;
}
