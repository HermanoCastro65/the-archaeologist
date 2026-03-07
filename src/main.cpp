#include <iostream>
#include <string>

#include "archaeologist/runner/self_runner.h"

int main(int argc, char **argv) {

  std::cout << "The Archaeologist\n";
  std::cout << "Codebase exploration tool\n";

  std::string path = ".";

  if (argc > 1) {
    path = argv[1];
  }

  std::cout << "Analyzing: " << path << "\n";

  archaeologist::SelfRunner runner;
  runner.run(path);

  return 0;
}