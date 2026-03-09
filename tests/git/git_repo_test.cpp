#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

#include "archaeologist/git/repo_scanner.h"

using namespace archaeologist;

static bool git_available() {
  int result = std::system("git --version >nul 2>&1");
  return result == 0;
}

void git_repository_clone_and_cleanup() {

  if (!git_available()) {
    // skip test if git is not installed
    return;
  }

  std::string repo = "https://github.com/octocat/Hello-World.git";

  std::filesystem::path path = RepoScanner::clone(repo);

  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("Repository was not cloned");
  }

  bool has_files = false;

  for (auto &p : std::filesystem::recursive_directory_iterator(path)) {

    if (p.is_regular_file()) {
      has_files = true;
      break;
    }
  }

  if (!has_files) {
    throw std::runtime_error("Cloned repository has no files");
  }

  RepoScanner::cleanup(path);

  if (std::filesystem::exists(path)) {
    throw std::runtime_error("Cleanup failed");
  }
}