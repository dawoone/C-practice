// g++ -pthread -std=gnu++17 pthread_cond.cpp

#include <pthread.h>

#include <chrono>
#include <iostream>
#include <thread>

void timer_func(int a, pthread_cond_t& cv, pthread_mutex_t& cv_mutex) {
  std::cout << "start timer. " << a << std::endl;

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  ts.tv_sec += a;
  pthread_mutex_lock(&cv_mutex);
  int rc = pthread_cond_timedwait(&cv, &cv_mutex, &ts);

  if (rc != ETIMEDOUT) {
    std::cout << "wake up from signal" << std::endl;
  } else {
    std::cout << "wake up from timeout" << std::endl;
  }

  pthread_mutex_unlock(&cv_mutex);
  std::cout << "end timer. " << a << std::endl;
}

int main(void) {
  // Declare the necessary variables
  pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_condattr_t m_attr;
  pthread_cond_t m_cond;

  // Set clock to monotonic
  pthread_condattr_init(&m_attr);
  pthread_condattr_setclock(&m_attr, CLOCK_MONOTONIC);
  pthread_cond_init(&m_cond, &m_attr);

  std::thread timer_thread1(timer_func, 5, std::ref(m_cond), std::ref(m_mutex));
  std::thread timer_thread2(timer_func, 10, std::ref(m_cond), std::ref(m_mutex));
  std::thread timer_thread3(timer_func, 20, std::ref(m_cond), std::ref(m_mutex));

  std::this_thread::sleep_for(std::chrono::seconds(2));

  // pthread_cond_signal(&m_cond);
  pthread_cond_broadcast(&m_cond);

  timer_thread1.join();
  timer_thread2.join();
  timer_thread3.join();
}
