#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <gtest/gtest_prod.h>

#include <memory>
#include <thread>

class StateMachine {
 public:
  FRIEND_TEST(StateMachineTest, Run);
  FRIEND_TEST(StateMachineTest, Run2);

  enum class State { DEFAULT, A_UP, A_DOWN, B_UP, B_DOWN };

  StateMachine() : state_(State::DEFAULT), flag_a_(false), flag_b_(false), done_(false) {}

  void Run();
  void Worker();
  void ShutDown();

 private:
  State state_;
  bool flag_a_;
  bool flag_b_;

  bool done_;

  std::unique_ptr<std::thread> worker_thread_;
};

void func();

#endif  // STATE_MACHINE_HPP
