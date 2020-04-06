#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

void timer_func(int a, std::condition_variable& cv, std::mutex& cv_mutex) {
  std::cout << "start timer. " << a << std::endl;

  std::unique_lock lock(cv_mutex);

  auto now = std::chrono::system_clock::now();
  cv.wait_until(lock, now + std::chrono::seconds(a));

  std::cout << "end timer. " << a << std::endl;
}

int main() {
  std::condition_variable cv;
  std::mutex cv_mutex;

  std::thread timer_thread1(timer_func, 30, std::ref(cv), std::ref(cv_mutex));
  std::thread timer_thread2(timer_func, 60, std::ref(cv), std::ref(cv_mutex));

  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::cout << "5s elapsed" << std::endl;

  cv.notify_all();

  timer_thread1.join();
  timer_thread2.join();
  return 0;
}
