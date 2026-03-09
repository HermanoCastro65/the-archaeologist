#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "archaeologist/scanner/directory_scanner.h"

namespace fs = std::filesystem;

void scanner_respects_ignore_config() {

  std::cout << "Running scanner_respects_ignore_config\n";

  fs::path temp = fs::temp_directory_path() / "archaeologist_ignore_config_test";

  fs::create_directories(temp / "src");
  fs::create_directories(temp / ".ruff_cache");

  std::ofstream(temp / "src" / "main.cpp");
  std::ofstream(temp / ".ruff_cache" / "cache_file");
  std::ofstream(temp / "temp.pyc");

  archaeologist::DirectoryScanner scanner;

  auto files = scanner.scan(temp);

  bool found_cpp = false;
  bool found_cache = false;
  bool found_pyc = false;

  for (auto &f : files) {

    auto name = f.filename().string();

    if (name == "main.cpp")
      found_cpp = true;

    if (name == "cache_file")
      found_cache = true;

    if (name == "temp.pyc")
      found_pyc = true;
  }

  assert(found_cpp);
  assert(!found_cache);
  assert(!found_pyc);

  fs::remove_all(temp);
}