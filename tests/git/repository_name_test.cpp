#include <stdexcept>
#include <string>

#include "archaeologist/git/repo_scanner.h"

void repository_name_extracted_from_url() {

  std::string url = "https://github.com/user/the-archaeologist.git";

  std::string name = archaeologist::RepoScanner::repository_name(url);

  if (name != "the-archaeologist") {
    throw std::runtime_error("Repository name extraction failed");
  }
}