#pragma once

#include <iostream>
#include <string>

struct TestStats {
  int total = 0;
  int passed = 0;
};

inline TestStats stats;

inline void run_test(const std::string &name, void (*test_func)()) {
  stats.total++;

  try {
    test_func();
    stats.passed++;
    std::cout << "[PASS] " << name << "\n";
  } catch (...) {
    std::cout << "[FAIL] " << name << "\n";
  }
}

inline void print_summary() {
  int failed = stats.total - stats.passed;
  double percent = stats.total ? (100.0 * stats.passed / stats.total) : 0.0;

  std::cout << "\nTests run: " << stats.total << "\n";
  std::cout << "Passed: " << stats.passed << "\n";
  std::cout << "Failed: " << failed << "\n";
  std::cout << "Success rate: " << percent << "%\n";
}