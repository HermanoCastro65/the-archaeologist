#include <filesystem>
#include <stdexcept>
#include <vector>

#include "archaeologist/scanner/directory_scanner.h"

void tree_starts_from_repository_root() {

  std::filesystem::path root = "repo";

  std::vector<std::filesystem::path> files = {root / "src/main.cpp", root / "src/engine.cpp",
                                              root / "include/engine.h"};

  archaeologist::DirectoryScanner scanner;

  // this should not throw
  scanner.tree(files, root);
}