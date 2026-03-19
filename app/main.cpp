#include "logger/consolesink.hpp"
#include "logger/filesink.hpp"
#include "logger/logger.hpp"
#include <memory>
#include <thread>

#define KB 1024

int main() {
  logger::Logger logger;

  logger.register_sink(std::make_shared<logger::ConsoleSink>());
  logger.register_sink(std::make_shared<logger::FileSink>("./logs/", 100 * KB));

  std::vector<std::thread> threads;

  for (int t = 0; t < 4; ++t) {
    threads.emplace_back([&logger, t]() {
      for (int i = 0; i < 500; ++i) {
        logger.info("thread_" + std::to_string(t),
                    "message " + std::to_string(i));
      }
    });
  }

  for (auto &th : threads)
    th.join();

  return 0;
}
