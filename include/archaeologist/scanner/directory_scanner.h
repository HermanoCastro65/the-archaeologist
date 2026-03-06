#pragma once

#include <filesystem>
#include <vector>

namespace archaeologist {

class DirectoryScanner {
public:
  std::vector<std::filesystem::path> scan(const std::filesystem::path &root);
};

} // namespace archaeologist