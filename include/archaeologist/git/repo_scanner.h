#pragma once

#include <filesystem>
#include <string>

namespace archaeologist {

class RepoScanner {
public:
  static std::filesystem::path clone(const std::string &url);
  static void cleanup(const std::filesystem::path &path);
  static std::string repository_name(const std::string &url);
  static bool looks_like_git_repo(const std::string &url);
};

} // namespace archaeologist