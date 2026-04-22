#include "logger/logsink.hpp"
#include <fstream>
#include <memory>
#include <mutex>
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
   * @param file_path Directory or path prefix used to create log files.
   * @param max_file_size Maximum size of a single log file before rotation.
   */
  FileSink(const std::string &file_path, const std::size_t max_file_size);

  /**
   * @brief Creates new FileSink with a custom formatter.
   *
   * @param file_path Directory or path prefix used to create log files.
   * @param max_file_size Maximum size of a single log file before rotation.
   * @param formatter Formatter used to convert log entries to strings.
   */
  FileSink(const std::string &file_path, const std::size_t max_file_size,
           std::shared_ptr<LogFormatter> formatter);

  /**
   * @brief Outputs log entry to a file
   *
   * @param entry Log entry to write.
   */
  void log(const LogEntry &entry) override;

private:
  /**
   * @brief Stream to write log entries to file.
   */
  std::ofstream fstream_;

  /**
   * @brief Mutex for writes and file rotation.
   */
  std::mutex mut_;

  /**
   * @brief Path of file to be written.
   */
  std::string file_path_;

  /**
   * @brief Maximum size of one log file in bytes.
   */
  std::size_t max_file_size_;

  /**
   * @brief Size of currently open log file.
   */
  std::size_t current_size_;

  /**
   * @brief Number added at the end of the file name.
   */
  std::size_t current_file_index_;

  /**
   * @brief Builds file name.
   *
   * @return Generated log file path.
   */
  std::string getFileName();

  /**
   * @brief Close current file and open a new one.
   */
  void rotateFile();
};
} // namespace logger
