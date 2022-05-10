//------------------------------------------------------------------------------
//
// Generic code to test different variants of vector add
// Avoiding tons of boilerplate otherwise
//
// Macros to control things:
//  * inherited from testers.hpp: RUNHOST, MEASURE_NORMAL, INORD...
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#pragma once

#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

#include <CL/sycl.hpp>

// problems with boost in OneAPI console on Windows
#ifdef USE_BOOST_OPTPARSE
#include "optparse.hpp"
#else
#include "optparse_alt.hpp"
#endif

#include "testers.hpp"

// defaults
constexpr int LIST_SIZE = 1024 * 2;
constexpr int NREPS = 10;

namespace sycltesters {

template <typename T> class VectorAdd {
  cl::sycl::queue DeviceQueue_;

public:
  using type = T;
  VectorAdd(cl::sycl::queue &DeviceQueue) : DeviceQueue_(DeviceQueue) {}
  virtual EvtRet_t operator()(T const *AVec, T const *BVec, T *CVec,
                              size_t Sz) = 0;
  cl::sycl::queue &Queue() { return DeviceQueue_; }
  const cl::sycl::queue &Queue() const { return DeviceQueue_; }
  virtual ~VectorAdd() {}
};

template <typename T> struct VectorAddHost : public VectorAdd<T> {
public:
  VectorAddHost(cl::sycl::queue &DeviceQueue) : VectorAdd<T>(DeviceQueue) {}
  EvtRet_t operator()(T const *AVec, T const *BVec, T *CVec,
                      size_t Sz) override {
    for (size_t I = 0; I < Sz; ++I)
      CVec[I] = AVec[I] + BVec[I];
    return {}; // nothing to construct as event
  }
};

template <typename T> class VectorAddTester {
  std::vector<T> A_, B_, C_;
  VectorAdd<T> &Vadder_;
  Timer Timer_;
  unsigned Sz_;
  unsigned Rep_;

public:
  VectorAddTester(VectorAdd<T> &Vadder, unsigned Sz, unsigned Rep)
      : Vadder_(Vadder), Sz_(Sz), Rep_(Rep) {
    A_.resize(Sz_);
    B_.resize(Sz_);
    C_.resize(Sz_);
  }

  void initialize() {
    for (int i = 0; i < Sz_; i++) {
      A_[i] = i;
      B_[i] = Sz_ - i;
      C_[i] = 0;
    }
  }

  // to have perf measurements we are doing in loop:
  // C = A + B;
  // A = B + C;
  // B = C + A;
  std::pair<unsigned, unsigned> calculate() {
    // timer start
    unsigned EvtTiming = 0;
    std::cout << "Nreps = " << Rep_ << std::endl;
    Timer_.start();
    // loop
    for (int i = 0; i < Rep_; ++i) {
      EvtRet_t Ret;
      Ret = Vadder_(A_.data(), B_.data(), C_.data(), Sz_);
      EvtTiming += getTime(Ret);
      Ret = Vadder_(B_.data(), C_.data(), A_.data(), Sz_);
      EvtTiming += getTime(Ret);
      Ret = Vadder_(C_.data(), A_.data(), B_.data(), Sz_);
      EvtTiming += getTime(Ret);
    }
    Timer_.stop();
    return {Timer_.elapsed(), EvtTiming};
  }
};

template <typename VaddChildT> void test_sequence(int argc, char **argv) {
  std::cout << "Welcome to vector addition" << std::endl;

  try {
    unsigned Size = 0, NReps = 0;

    optparser_t OptParser;
    OptParser.template add<int>("size", LIST_SIZE, "size of vectors to add");
    OptParser.template add<int>("nreps", NREPS,
                                "number of repetitions in tester loop");
    OptParser.parse(argc, argv);

    Size = OptParser.template get<int>("size");
    NReps = OptParser.template get<int>("nreps");

    std::cout << "Using vector size = " << Size << std::endl;
    std::cout << "Using #of repetitions = " << NReps << std::endl;

    auto Q = set_queue();
    print_info(std::cout, Q.get_device());

#ifdef MEASURE_NORMAL
    VectorAddHost<int> VaddH{Q}; // Q unused for this derived class
    VectorAddTester<int> TesterH{VaddH, Size, NReps};
    TesterH.initialize();
    auto ElapsedH = TesterH.calculate();
    std::cout << "Measured host time: " << ElapsedH.first << std::endl;
#endif

    VaddChildT Vadd{Q};
    VectorAddTester<typename VaddChildT::type> Tester{Vadd, Size, NReps};

    std::cout << "Initializing" << std::endl;
    Tester.initialize();

    std::cout << "Calculating" << std::endl;
    auto Elapsed = Tester.calculate();

    std::cout << "Measured time: " << Elapsed.first / 1000.0 << std::endl;
    std::cout << "Pure execution time: " << Elapsed.second / 1000000000.0
              << std::endl;
  } catch (cl::sycl::exception const &err) {
    std::cerr << "SYCL ERROR: " << err.what() << "\n";
    abort();
  } catch (std::exception const &err) {
    std::cerr << "Exception: " << err.what() << "\n";
    abort();
  } catch (...) {
    std::cerr << "Unknown error\n";
    abort();
  }
  std::cout << "Everything is correct" << std::endl;
}

} // namespace sycltesters