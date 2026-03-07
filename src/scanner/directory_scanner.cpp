#include "archaeologist/scanner/directory_scanner.h"

#include <iostream>

namespace archaeologist {

std::vector<std::filesystem::path> DirectoryScanner::scan(const std::filesystem::path &root) {

  std::vector<std::filesystem::path> files;

  for (auto it = std::filesystem::recursive_directory_iterator(root);
       it != std::filesystem::recursive_directory_iterator(); ++it) {

    const auto &entry = *it;
    auto path = entry.path();

    if (entry.is_directory()) {

      std::string name = path.filename().string();

      if (name == ".git" || name == "build") {
        it.disable_recursion_pending();
        continue;
      }
    }

    if (entry.is_regular_file()) {
      files.push_back(path);
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