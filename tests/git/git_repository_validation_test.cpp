#include <stdexcept>
#include <string>

#include "archaeologist/git/repo_scanner.h"

void git_repository_validation() {

  std::string valid_repo = "https://github.com/octocat/Hello-World";

  if (!archaeologist::RepoScanner::repository_exists(valid_repo)) {
    throw std::runtime_error("Valid repository was not detected");
  }

  std::string invalid_repo = "https://github.com/octocat/non-existent-repo-xyz123";

  if (archaeologist::RepoScanner::repository_exists(invalid_repo)) {
    throw std::runtime_error("Invalid repository incorrectly detected");
  }
}