#include <cassert>
#include <filesystem>
#include <iostream>
#include <sstream>

#include "archaeologist/scanner/directory_scanner.h"

namespace fs = std::filesystem;

void self_runner_scans_project() {
  std::cout << "Running self_runner_scans_project\n";

  archaeologist::DirectoryScanner scanner;

  auto files = scanner.scan(".");

  assert(files.size() > 0);
}