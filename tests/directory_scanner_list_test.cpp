#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "archaeologist/scanner/directory_scanner.h"

namespace fs = std::filesystem;

void directory_scanner_list_outputs_files() {
  std::cout << "Running directory_scanner_list_outputs_files\n";

  fs::path temp = fs::temp_directory_path() / "archaeologist_list_test";
  fs::create_directories(temp);

  std::ofstream(temp / "file1.cpp");
  std::ofstream(temp / "file2.h");

  archaeologist::DirectoryScanner scanner;

  auto files = scanner.scan(temp);

  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  scanner.list(files);

  std::cout.rdbuf(old);

  std::string output = buffer.str();

  assert(output.find("file1.cpp") != std::string::npos);
  assert(output.find("file2.h") != std::string::npos);

  fs::remove_all(temp);
}