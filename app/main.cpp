#include "logger/consolesink.hpp"
#include "logger/filesink.hpp"
#include "logger/logger.hpp"
#include "logger/networksink.hpp"
#include <chrono>
#include <memory>
#include <thread>

#define KB 1024

int main() {
  logger::Logger logger;

  logger.register_sink(
      std::make_shared<logger::NetworkSink>("localhost", 9000));
  for (int i = 0; i < 20; ++i) {
    logger.info("overflow", "msg " + std::to_string(i));
  }

  std::this_thread::sleep_for(std::chrono::seconds(10));
  return 0;
}
