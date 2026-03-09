#include "archaeologist/git/repo_scanner.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace archaeologist {

std::filesystem::path RepoScanner::clone(const std::string &url) {

  std::filesystem::path temp = std::filesystem::temp_directory_path() / "archaeologist_repo";

  if (std::filesystem::exists(temp)) {
    std::filesystem::remove_all(temp);
  }

  std::string command = "git clone --depth 1 " + url + " " + temp.string();

  std::cout << "Cloning repository...\n";

  int result = std::system(command.c_str());

  if (result != 0) {
    throw std::runtime_error("Failed to clone repository");
  }

  return temp;
}

void RepoScanner::cleanup(const std::filesystem::path &path) {

  if (std::filesystem::exists(path)) {
    std::filesystem::remove_all(path);
  }
}

} // namespace archaeologist