//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// profile-guided optimizations benchmark
//
// without PGO:
// > g++ pgotest.cc -O2 -o test.x
// > ./test.x
//
// collecting profile:
// > g++ -fprofile-generate pgotest.cc -O2 -o test-pg.x
// > ./test-pg.x
//
// with PGO:
// > g++ -fprofile-use pgotest.cc -O2 -o test-profiled.x
// > ./test-profiled.x
//
//-----------------------------------------------------------------------------

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

namespace chr = std::chrono;

constexpr int bigsize = (1 << 27);

int main() {
  int n = bigsize, divisor = 2, k = 0;
  std::vector<char> data(n);
  std::generate(data.begin(), data.end(), [k, divisor]() mutable {
    k = (k + 1) % divisor;
    return k;
  });
  auto tstart = chr::high_resolution_clock::now();
  std::sort(data.begin(), data.end());
  auto tfin = chr::high_resolution_clock::now();
  auto ms = chr::duration_cast<chr::milliseconds>(tfin - tstart).count();
  std::cout << "Elapsed: " << ms << std::endl;
}
