#include "logger/logsink.hpp"
#include <fstream>
#include <string>

namespace logger {

/**
 * @brief Sink outputting log entries to a file.
 */
class FileSink : public LogSink {
public:
  /**
   * @brief Creates new FileSink for given file path
   *
   * @param path Path to output file
   */
  FileSink(const std::string &file_path, const std::size_t max_file_size);
  /**
   * @brief Outputs log entry to a file
   */
  void log(const LogEntry &entry) override;

private:
  std::ofstream fstream;
  std::mutex mut;
  std::string file_path;
  std::size_t max_file_size;
  std::size_t current_size;

  std::string getFileName();
  void rotateFile();
};
} // namespace logger
