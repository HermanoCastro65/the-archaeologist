#include <filesystem>
#include <stdexcept>

#include "archaeologist/git/repo_scanner.h"

using namespace archaeologist;

void git_repository_clone_and_cleanup() {

  auto repo = "https://github.com/octocat/Hello-World.git";

  auto path = RepoScanner::clone(repo);

  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("Repository was not cloned");
  }

  bool has_file = false;

  for (auto &p : std::filesystem::recursive_directory_iterator(path)) {
    if (p.is_regular_file()) {
      has_file = true;
      break;
    }
  }

  if (!has_file) {
    throw std::runtime_error("Repository clone is empty");
  }

  RepoScanner::cleanup(path);
}