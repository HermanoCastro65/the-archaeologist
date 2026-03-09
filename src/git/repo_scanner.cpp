#include "archaeologist/git/repo_scanner.h"

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

namespace archaeologist {

std::filesystem::path RepoScanner::clone(const std::string &url) {

  auto temp = std::filesystem::temp_directory_path() /
              ("archaeologist_repo_" + std::to_string(std::time(nullptr)));

  std::string command = "git clone --depth 1 --filter=blob:none " + url + " " + temp.string();

  int result = std::system(command.c_str());

  if (result != 0) {
    throw std::runtime_error("Failed to clone repository");
  }

  return temp;
}

void RepoScanner::cleanup(const std::filesystem::path &path) {

  if (!std::filesystem::exists(path))
    return;

  // Windows sometimes locks git pack files briefly
  for (int i = 0; i < 5; i++) {

    try {

      std::filesystem::remove_all(path);

      if (!std::filesystem::exists(path))
        return;

    } catch (...) {
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  std::cerr << "Warning: temporary repository cleanup failed\n";
}

} // namespace archaeologist