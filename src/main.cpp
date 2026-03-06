#include <iostream>

int main(int argc, char **argv) {
  std::cout << "The Archaeologist\n";
  std::cout << "Codebase exploration tool\n";

  if (argc > 1) {
    std::cout << "Analyzing: " << argv[1] << "\n";
  }

  return 0;
}