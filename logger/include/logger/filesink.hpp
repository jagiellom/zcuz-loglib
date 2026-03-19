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
  std::ofstream fstream_;
  std::mutex mut_;
  std::string file_path_;
  std::size_t max_file_size_;
  std::size_t current_size_;

  std::string getFileName();
  void rotateFile();
};
} // namespace logger
