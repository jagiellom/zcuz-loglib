#include "logger/filesink.hpp"
#include "logger/loglevel.hpp"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace logger {

FileSink::FileSink(const std::string &path, const std::size_t max_size)
    : file_path(path), max_file_size(max_size), current_size(0) {

  std::filesystem::create_directories(
      std::filesystem::path(path).parent_path());

  auto file_name = getFileName();
  fstream.open(file_name, std::ios::app);

  if (!fstream.is_open())
    throw std::runtime_error("Error while opening log file");
}

std::string FileSink::getFileName() {

  std::stringstream ss;

  auto now = std::chrono::system_clock::now();
  ss << file_path << "log" << "-" << getTimestamp(now) << ".log";

  return ss.str();
}

void FileSink::rotateFile() {
  fstream.close();

  auto new_file_name = getFileName();
  current_size = 0;

  fstream.open(new_file_name, std::ios::app);

  if (!fstream.is_open())
    throw std::runtime_error("Error while opening new log file");
}

void FileSink::log(const LogEntry &entry) {
  std::lock_guard<std::mutex> lock(mut);

  std::stringstream ss;

  ss << "[" << logLevelToString(entry.level) << "] ["
     << getTimestamp(entry.timestamp) << "] [" << entry.module << "] "
     << entry.msg << "\n";

  std::string line = ss.str();
  if (current_size + line.size() > max_file_size) {
    rotateFile();
  }

  fstream << line;
  current_size += line.size();
}

} // namespace logger
