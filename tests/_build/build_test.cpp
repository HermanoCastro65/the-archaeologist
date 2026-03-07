#include <cassert>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void build_artifact_test() {
  std::cout << "Running build artifact test\n";

#ifdef _WIN32
  fs::path exe = "build/the_archaeologist.exe";
#else
  fs::path exe = "build/the_archaeologist";
#endif

  assert(fs::exists(exe));

  std::cout << "Build artifact exists\n";
}