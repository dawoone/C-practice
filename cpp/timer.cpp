#include <atomic>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>

class Timer {
 public:
  struct SleepInfo {
    int64_t expiration_time;
    bool &flag_to_set;
  };

  enum class Id : int {
    TIMER_5_A,
    TIMER_5_B,
    TIMER_30_A,
    TIMER_30_B,
    TIMER_60,
  };

  explicit Timer(pthread_cond_t &cv)
      : timer_caller_wait_cv_(cv), running_(false) {}
  ~Timer();

  void Start();
  void Stop();

  void Register(Id, bool &flag);
  void Unregister(Id);

 private:
  void Loop();
  void CheckAndUpdateFlagsIfExpired();
  bool IsRegistered(Id id);
  int64_t GetTime();
  int64_t GetExpiritaionTime(Id);

  std::unique_ptr<std::thread> loop_thread_;
  std::map<Id, SleepInfo> map_;
  std::mutex map_mtx_;
  pthread_cond_t &timer_caller_wait_cv_;
  std::atomic<bool> running_;
};

Timer::~Timer() {
  if (!running_) {
    Stop();
  }
  if (loop_thread_->joinable()) {
    std::cout << "~Timer. Wait for loop_thread to be finished." << std::endl;
    loop_thread_->join();
    std::cout << "loop_thread joined" << std::endl;
  }
}

void Timer::Start() {
  running_ = true;
  loop_thread_ = std::make_unique<std::thread>(&Timer::Loop, this);
}

void Timer::Loop() {
  while (running_) {
    try {
      CheckAndUpdateFlagsIfExpired();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "timer awaken at " << GetTime() << std::endl;
    } catch (const std::exception &e) {
      std::cout << "err: " << e.what() << std::endl;
    }
  }
}

void Timer::Stop() { running_ = false; }

void Timer::CheckAndUpdateFlagsIfExpired() {
  std::lock_guard guard(map_mtx_);

  int64_t current_time = GetTime();
  for (auto it = map_.begin(); it != map_.end();) {
    if (current_time > it->second.expiration_time) {
      it->second.flag_to_set = true;
      it = map_.erase(it);
      pthread_cond_broadcast(&timer_caller_wait_cv_);
      std::cout << "Timer expired. id=" << static_cast<int>(it->first)
                << " removed from entry" << std::endl;
    } else {
      ++it;
    }
  }
}

void Timer::Register(Id id, bool &flag_to_set) {
  if (IsRegistered(id)) {
    std::cout << "Cannot register timer. id=" << static_cast<int>(id)
              << " already registered." << std::endl;
    return;
  }

  std::lock_guard guard(map_mtx_);
  int64_t expiration_time = GetExpiritaionTime(id);
  map_.emplace(id, SleepInfo{expiration_time, flag_to_set});
  std::cout << "Timer registered. id=" << static_cast<int>(id)
            << ", expiration_time=" << expiration_time << std::endl;
}

void Timer::Unregister(Id id) {
  if (!IsRegistered(id)) {
    std::cout << "Cannot unregister timer. id=" << static_cast<int>(id)
              << "isn't registered." << std::endl;
    return;
  }

  std::lock_guard guard(map_mtx_);
  map_.erase(map_.find(id));
  std::cout << "Timer unregistered. id=" << static_cast<int>(id) << std::endl;
}

bool Timer::IsRegistered(Id id) {
  std::lock_guard guard(map_mtx_);
  return map_.find(id) != map_.end();
}

int64_t Timer::GetExpiritaionTime(Timer::Id id) {
  int64_t expiration_time = 0;
  switch (id) {
    case Id::TIMER_5_A:
    case Id::TIMER_5_B:
      expiration_time = GetTime() + 5;
      break;
    case Id::TIMER_30_A:
    case Id::TIMER_30_B:
      expiration_time = GetTime() + 30;
      break;
    case Id::TIMER_60:
      expiration_time = GetTime() + 60;
      break;
  }
  return expiration_time;
}

int64_t Timer::GetTime() {
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  return ts.tv_sec;
}

int main() {
  pthread_mutex_t cv_mutex;
  pthread_cond_t cv;
  pthread_cond_init(&cv, nullptr);
  pthread_mutex_init(&cv_mutex, nullptr);

  Timer timer(cv);
  timer.Start();

  bool flag_a = false;
  bool flag_b = false;
  timer.Register(Timer::Id::TIMER_5_A, flag_a);
  timer.Register(Timer::Id::TIMER_5_A, flag_a);
  timer.Register(Timer::Id::TIMER_5_B, flag_b);

  while (true) {
    std::cout << "flag_a=" << flag_a << std::endl;
    std::cout << "flag_b=" << flag_b << std::endl;

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    ts.tv_sec += 10;

    int rc = pthread_cond_timedwait(&cv, &cv_mutex, &ts);
    if (rc == ETIMEDOUT) {
      std::cout << "timed out" << std::endl;
      break;
    } else {
      std::cout << "signal out" << std::endl;
    }
  }

  timer.Stop();
  std::cout << "end" << std::endl;

  return 0;
}