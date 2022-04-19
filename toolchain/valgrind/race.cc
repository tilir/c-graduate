//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// valgrind race condition example
//
// > g++ race.cc -pthread
// > valgrind --tool=helgrind ./a.out
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <thread>
int x = 0;

void foo() {
  auto t = std::thread([&] { ++x; });
  t.detach();
  ++x;
}

int main() {
  foo();
  std::cout << x << std::endl;
  return 0;
}
