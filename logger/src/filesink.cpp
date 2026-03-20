#include "logger/filesink.hpp"
#include "logger/loglevel.hpp"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace logger {

FileSink::FileSink(const std::string &path, const std::size_t max_size)
    : file_path_(path), max_file_size_(max_size), current_size_(0) {

  std::filesystem::create_directories(
      std::filesystem::path(path).parent_path());

  auto file_name = getFileName();
  fstream_.open(file_name, std::ios::app);

  if (!fstream_.is_open())
    throw std::runtime_error("Error while opening log file");
}

std::string FileSink::getFileName() {

  std::stringstream ss;

  auto now = std::chrono::system_clock::now();
  ss << file_path_ << "log" << "-" << getTimestamp(now) << ".log";

  return ss.str();
}

void FileSink::rotateFile() {
  fstream_.close();

  auto new_file_name = getFileName();
  current_size_ = 0;

  fstream_.open(new_file_name, std::ios::app);

  if (!fstream_.is_open())
    throw std::runtime_error("Error while opening new log file");
}

void FileSink::log(const LogEntry &entry) {
  std::lock_guard<std::mutex> lock(mut_);

  std::stringstream ss;

  ss << "[" << logLevelToString(entry.level) << "] ["
     << getTimestamp(entry.timestamp) << "] [" << entry.module << "] "
     << entry.msg << "\n";

  std::string line = ss.str();
  if (current_size_ + line.size() > max_file_size_) {
    rotateFile();
  }

  fstream_ << line;
  current_size_ += line.size();
}

} // namespace logger
