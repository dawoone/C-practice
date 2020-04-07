#include <iostream>
#include <memory>

class A {
 public:
  A() { std::cout << "A constructed" << std::endl; }
  ~A() { std::cout << "A destructed" << std::endl; }

  void Print() { std::cout << "Hello" << std::endl; }
  void Print2() { std::cout << "World" << std::endl; }
};

A* func() {
  // A obj;
  A* obj = new A();
  obj->Print();

  return obj;
}

std::unique_ptr<A> smart_func() {
  std::unique_ptr<A> obj = std::make_unique<A>();
  obj->Print();

  return obj;
}

void sample(std::unique_ptr<A>& o) { o->Print(); }
void sample2(std::unique_ptr<A> o) { o->Print(); }

int main() {
  //  A* ret = func();
  //  ret->Print2();
  //  delete ret;

  std::unique_ptr<A> ret = smart_func();
  ret->Print2();

  //  std::cout << "============" << std::endl;
  //  sample(ret);
  //  std::cout << "##############" << std::endl;
  //  sample2(std::move(ret));
  //  std::cout << "sample 2 finished" << std::endl;

  // ...

  //  std::unique_ptr<A> ret;
  //  if (ret && ret->joinable()) ret->join();
  //  ret.reset();
  //  ret = std::make_unique<A>();

  return 0;
}
