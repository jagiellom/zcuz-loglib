#include <condition_variable>
#include <mutex>
#include <queue>
namespace logger {

template <typename T> class ThreadSafeQueue {

public:
  void push(T val) {
    {
      std::lock_guard<std::mutex> lock(mut_);
      if (closed_)
        throw std::string(
            "Cannot push value to queue. ThreadSafeQueue is closed.");
      queue_.push(std::move(val));
    }

    condition_.notify_one();
  }

  bool try_pop(T &out) {
    std::unique_lock<std::mutex> lock(mut_);
    condition_.wait(lock, [this] { return closed_ || !queue_.empty(); });

    if (queue_.empty()) {
      return false;
    }

    out = std::move(queue_.front());
    queue_.pop();

    return true;
  }

  void close() {
    std::lock_guard<std::mutex> lock(mut_);
    closed_ = true;
    condition_.notify_all();
  }

private:
  std::queue<T> queue_;
  std::mutex mut_;
  std::condition_variable condition_;
  bool closed_ = false;
};

} // namespace logger
