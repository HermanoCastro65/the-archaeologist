#include <stdexcept>
#include <string>

#include "archaeologist/git/repo_scanner.h"

void invalid_git_repository_detection() {

  std::string invalid = "https://github.com/user";

  if (archaeologist::RepoScanner::looks_like_git_repo(invalid)) {
    throw std::runtime_error("Invalid repository incorrectly detected as valid");
  }

  std::string valid = "https://github.com/user/project.git";

  if (!archaeologist::RepoScanner::looks_like_git_repo(valid)) {
    throw std::runtime_error("Valid repository not detected");
  }
}