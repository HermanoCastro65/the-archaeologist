#pragma once

#include <filesystem>
#include <vector>

namespace archaeologist {

class DirectoryScanner {
public:
  std::vector<std::filesystem::path> scan(const std::filesystem::path &root);

  void list(const std::vector<std::filesystem::path> &files);
  void tree(const std::vector<std::filesystem::path> &files);
};

} // namespace archaeologist