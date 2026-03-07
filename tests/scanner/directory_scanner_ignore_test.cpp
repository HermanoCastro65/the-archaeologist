#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "archaeologist/scanner/directory_scanner.h"

namespace fs = std::filesystem;

void directory_scanner_ignores_build_and_git() {
  std::cout << "Running directory_scanner_ignores_build_and_git\n";

  fs::path temp = fs::temp_directory_path() / "archaeologist_ignore_test";

  fs::create_directories(temp / ".git");
  fs::create_directories(temp / "build");

  fs::create_directories(temp / "src");

  std::ofstream(temp / ".git" / "object_file");
  std::ofstream(temp / "build" / "artifact.o");
  std::ofstream(temp / "src" / "main.cpp");

  archaeologist::DirectoryScanner scanner;

  auto files = scanner.scan(temp);

  bool found_src = false;
  bool found_git = false;
  bool found_build = false;

  for (auto &f : files) {
    auto path = f.string();

    if (path.find("main.cpp") != std::string::npos)
      found_src = true;

    if (path.find(".git") != std::string::npos)
      found_git = true;

    if (path.find("build") != std::string::npos)
      found_build = true;
  }

  assert(found_src);
  assert(!found_git);
  assert(!found_build);

  fs::remove_all(temp);
}