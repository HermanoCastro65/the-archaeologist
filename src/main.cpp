#include <iostream>

#include "archaeologist/runner/self_runner.h"

int main(int argc, char **argv) {
  std::cout << "The Archaeologist\n";
  std::cout << "Codebase exploration tool\n";

  if (argc > 1) {
    std::cout << "Analyzing: " << argv[1] << "\n";
  }

  archaeologist::SelfRunner runner;
  runner.run();

  return 0;
}