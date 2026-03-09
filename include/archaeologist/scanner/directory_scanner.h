#pragma once

#include "archaeologist/config/ignore_config.h"

#include <filesystem>
#include <vector>

namespace archaeologist {

class DirectoryScanner {
public:
  DirectoryScanner();

  std::vector<std::filesystem::path> scan(const std::filesystem::path &root);

  void list(const std::vector<std::filesystem::path> &files);
  void tree(const std::vector<std::filesystem::path> &files);

private:
  IgnoreConfig ignore;
};

} // namespace archaeologist