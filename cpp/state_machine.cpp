#include "state_machine.hpp"

#include <chrono>
#include <iostream>
#include <thread>

void func() { std::cout << "func" << std::endl; }

void StateMachine::Run() {
  std::cout << "State machine start" << std::endl;
  worker_thread_ = std::make_unique<std::thread>(&StateMachine::Worker, this);
  std::cout << "State machine end" << std::endl;
}

void StateMachine::Worker() {
  std::cout << "Worker start" << std::endl;

  while (!done_) {
    switch (state_) {
      case StateMachine::State::DEFAULT:
        std::cout << "default" << std ::endl;
        if (flag_a_ == true) {
          state_ = State::A_UP;
        } else if (flag_b_ == true) {
          state_ = State::B_UP;
        } else {
          std::cout << "no flag set" << std ::endl;
        }
        break;
      case StateMachine::State::A_UP:
        std::cout << "a_up" << std ::endl;
        flag_a_ = true;
        return;
        // break;
      case StateMachine::State::A_DOWN:
        flag_a_ = false;
        std::cout << "a_down" << std ::endl;
        break;
      case StateMachine::State::B_UP:
        flag_b_ = true;
        std::cout << "b_up" << std ::endl;
        break;
      case StateMachine::State::B_DOWN:
        flag_b_ = false;
        std::cout << "b_down" << std ::endl;
        break;
      default:
        std::cout << "Invalid state" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Worker end" << std::endl;
}

void StateMachine::ShutDown() {
  done_ = true;
  worker_thread_->join();
}
