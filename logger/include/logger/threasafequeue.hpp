#include <mutex>
#include <queue>
#include <semaphore>
namespace logger {

template <typename T> class ThreadSafeQueue {

public:
  void push(T val) {
    std::lock_guard<std::mutex> lock(mut);
    queue.push(std::move(val));

    semaphore.release();
  }

  T pop() {
    semaphore.acquire();
    std::unique_lock<std::mutex> lock(mut);

    T value = std::move(queue.front());

    queue.pop();

    return value;
  }

  bool is_empty() {
    std::unique_lock<std::mutex> lock(mut);
    queue.empty();
  }

private:
  std::queue<T> queue;
  std::mutex mut;
  std::counting_semaphore<INT_MAX> semaphore;
};

} // namespace logger
