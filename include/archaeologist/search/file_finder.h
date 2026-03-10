#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace archaeologist {

class FileFinder {

public:
  std::vector<std::filesystem::path> find(const std::vector<std::filesystem::path> &files,
                                          const std::string &filename);

  void print_file_content(const std::filesystem::path &path, const std::filesystem::path &root);

  void print_file_content(const std::filesystem::path &path);
};

} // namespace archaeologist