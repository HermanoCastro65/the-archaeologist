#include "archaeologist/runner/self_runner.h"
#include "archaeologist/scanner/directory_scanner.h"

#include <iostream>

namespace archaeologist {

void SelfRunner::run() {

  std::cout << "\nRunning Archaeologist self-runner...\n";
  std::cout << "Scanning project: .\n\n";

  DirectoryScanner scanner;

  auto files = scanner.scan(".");

  scanner.list(files);
}

} // namespace archaeologist