#include "archaeologist/scanner/directory_scanner.h"

#include <iostream>
#include <map>
#include <set>

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

void DirectoryScanner::tree(const std::vector<std::filesystem::path> &files) {

  std::map<std::filesystem::path, std::set<std::filesystem::path>> tree;

  for (const auto &file : files) {
    auto parent = file.parent_path();
    tree[parent].insert(file.filename());
  }

  for (const auto &[dir, children] : tree) {

    std::cout << dir.string() << "\n";

    for (const auto &child : children) {
      std::cout << "  └── " << child.string() << "\n";
    }

    std::cout << "\n";
  }
}

} // namespace archaeologist