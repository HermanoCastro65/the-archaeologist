#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "archaeologist/scanner/directory_scanner.h"

namespace fs = std::filesystem;

void directory_scanner_lists_files() {
  std::cout << "Running directory_scanner_lists_files\n";

  fs::path temp = fs::temp_directory_path() / "archaeologist_test";

  fs::create_directories(temp);

  std::ofstream(temp / "a.cpp");
  std::ofstream(temp / "b.h");

  archaeologist::DirectoryScanner scanner;

  std::vector<fs::path> files = scanner.scan(temp);

  assert(files.size() == 2);

  fs::remove_all(temp);
}