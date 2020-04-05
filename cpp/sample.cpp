#include <chrono>
#include <iostream>
#include <thread>

// void timer2(int& a) {
//  std::this_thread::sleep_for(std::chrono::seconds(a));
//  std::cout << "wake up after " << a << std::endl;
//}

class Uni {
 public:
  Uni() : f1_(false), f2_(false) {}

  void func();
  void run();

  void timer(int a, bool* flag);
  // void timer(const Uni* this, int a, bool* flag);

  static void static_timer(int a, bool* flag);

  bool f1() { return f1_; }
  bool f2() { return f2_; }

 private:
  bool f1_;
  bool f2_;
};

void Uni::func() {
  //  std::thread t2(&Uni::timer, this, 4, &f2_);
  //  std::this_thread::sleep_for(std::chrono::seconds(1));
  //  std::thread t1(&Uni::timer, this, 2, &f1_);

  std::thread t2(&Uni::static_timer, 4, &f2_);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::thread t1(&Uni::static_timer, 2, &f1_);

  // t.detach();
  t1.join();
  t2.join();

  // quit

  //
  //  std::thread t2(timer, a_);
  //  t2.join();
}

void Uni::timer(int time, bool* flag) {
  std::cout << "sleep for " << time << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(time));
  std::cout << "wake up after " << time << std::endl;
  *flag = true;
}

void Uni::static_timer(int time, bool* flag) {
  std::cout << "sleep for " << time << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(time));
  std::cout << "wake up after " << time << std::endl;
  *flag = true;
}

void Uni::run() {
  std::thread worker_thread(&Uni::func, this);
  // worker_thread.join();
}

void sample_thread_func(int* a) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  *a += 1;
}

void sample_thread(std::unique_ptr<std::thread>& p_thread) {
  int val = 0;
  // std::thread t(sample_thread_func, &val);
  p_thread = std::make_unique<std::thread>(sample_thread_func, &val);

  // t.join();
  // t.detach();
  std::cout << "val=" << val << std::endl;
}

int main() {
  //  Uni u;
  //  u.run();

  std::unique_ptr<std::thread> p_thread;
  sample_thread(std::unique_ptr<std::thread> & p_thread);
  p_thread.join();

  std::this_thread::sleep_for(std::chrono::seconds(2));

  // std::cout << "main end. flag1=" << u.f1() << ", flag2=" << u.f2() << std::endl;

  return 0;
}
