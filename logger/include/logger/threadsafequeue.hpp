#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>
namespace logger {

/**
 * @brief Blocking thread-safe FIFO queue.
 *
 * ThreadSafeQueue allows threads to push values while  consumer waits
 * for values with try_pop(). Closing the queue wakes consumers and
 * stops pushes.
 *
 * @tparam T Type stored in the queue.
 */
template <typename T> class ThreadSafeQueue {

public:
  /**
   * @brief Push value into the queue.
   *
   * @param val Value to push.
   * @throws std::runtime_error When the queue has been closed.
   */
  void push(T val) {
    {
      std::lock_guard<std::mutex> lock(mut_);
      if (closed_)
        throw std::runtime_error(
            "Cannot push value to queue. ThreadSafeQueue is closed.");
      queue_.push(std::move(val));
    }

    condition_.notify_one();
  }

  /**
   * @brief Wait and pop value from the queue.
   *
   * Blocks until queue is closed or populated
   *
   * @param out Popped value.
   * @return true when a value was popped, else false
   */
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

  /**
   * @brief Close the queue and wake consumers.
   *
   * Already queued values can still be popped after close(). New calls to
   * push() will fail.
   */
  void close() {
    std::lock_guard<std::mutex> lock(mut_);
    closed_ = true;
    condition_.notify_all();
  }

private:
  /**
   * @brief Queue values.
   */
  std::queue<T> queue_;

  /**
   * @brief Mutex for queue.
   */
  std::mutex mut_;

  /**
   * @brief Condition variable to wake consumers.
   */
  std::condition_variable condition_;

  /**
   * @brief Stores whether queue is closed.
   */
  bool closed_ = false;
};

} // namespace logger
