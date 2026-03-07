#include "archaeologist/scanner/directory_scanner.h"

#include <iostream>

namespace archaeologist {

std::vector<std::filesystem::path> DirectoryScanner::scan(const std::filesystem::path &root) {

  std::vector<std::filesystem::path> files;

  for (const auto &entry : std::filesystem::recursive_directory_iterator(root)) {

    if (entry.is_regular_file()) {
      files.push_back(entry.path());
    }
  }

  return files;
}

void DirectoryScanner::list(const std::vector<std::filesystem::path> &files) {
  for (const auto &file : files) {
    std::cout << file.string() << "\n";
  }
}

} // namespace archaeologist