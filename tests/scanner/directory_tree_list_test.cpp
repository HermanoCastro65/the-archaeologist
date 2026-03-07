#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "archaeologist/scanner/directory_scanner.h"

namespace fs = std::filesystem;

void directory_scanner_tree_list() {
  std::cout << "Running directory_scanner_tree_list\n";

  fs::path temp = fs::temp_directory_path() / "archaeologist_tree_test";

  fs::create_directories(temp / "src");
  fs::create_directories(temp / "tests");

  std::ofstream(temp / "src" / "main.cpp");
  std::ofstream(temp / "tests" / "test.cpp");

  archaeologist::DirectoryScanner scanner;

  auto files = scanner.scan(temp);

  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  scanner.tree(files);

  std::cout.rdbuf(old);

  std::string output = buffer.str();

  assert(output.find("src") != std::string::npos);
  assert(output.find("tests") != std::string::npos);
  assert(output.find("main.cpp") != std::string::npos);

  fs::remove_all(temp);
}