#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>
namespace logger {

/**
 * @brief Blocking thread-safe FIFO queue.
 *
 * ThreadSafeQueue allows producer threads to push values while a consumer waits
 * for values with try_pop(). Closing the queue wakes waiting consumers and
 * prevents further pushes.
 *
 * @tparam T Type stored in the queue.
 */
template <typename T> class ThreadSafeQueue {

public:
  /**
   * @brief Push a value into the queue.
   *
   * @param val Value to enqueue.
   * @throws std::runtime_error When the queue has already been closed.
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
   * @brief Wait for and pop the next value from the queue.
   *
   * This call blocks until either an item is available or the queue is closed.
   *
   * @param out Destination for the popped value.
   * @return true when a value was popped, false when the queue is closed and
   * empty.
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
   * @brief Close the queue and wake all waiting consumers.
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
   * @brief Stored queue values.
   */
  std::queue<T> queue_;

  /**
   * @brief Mutex protecting queue state.
   */
  std::mutex mut_;

  /**
   * @brief Condition variable used to wake waiting consumers.
   */
  std::condition_variable condition_;

  /**
   * @brief Whether the queue is closed for new values.
   */
  bool closed_ = false;
};

} // namespace logger
