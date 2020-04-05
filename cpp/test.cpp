#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "state_machine.hpp"

TEST(StateMachineTest, Run) {
  StateMachine machine;
  machine.Run();

  machine.flag_a_ = true;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  EXPECT_EQ(machine.state_, StateMachine::State::A_UP);

  machine.ShutDown();

  // std::this_thread::sleep_for(std::chrono::seconds(10));
}

TEST(StateMachineTest, Run2) {}
