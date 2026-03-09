#pragma once

#include <filesystem>
#include <string>

namespace archaeologist {

class RepoScanner {
public:
  static std::filesystem::path clone(const std::string &url);
  static void cleanup(const std::filesystem::path &path);
};

} // namespace archaeologist