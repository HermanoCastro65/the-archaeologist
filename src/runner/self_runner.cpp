#include "archaeologist/runner/self_runner.h"

#include <filesystem>
#include <iostream>

#include "archaeologist/git/repo_scanner.h"
#include "archaeologist/report/git_repository_report.h"
#include "archaeologist/report/project_report.h"
#include "archaeologist/scanner/directory_scanner.h"

namespace archaeologist {

static bool is_git_url(const std::string &path) {

  return path.rfind("http://", 0) == 0 || path.rfind("https://", 0) == 0 ||
         path.rfind("git@", 0) == 0;
}

void SelfRunner::run(const std::string &input) {

  std::cout << "Running The Archaeologist\n";
  std::cout << "Target: " << input << "\n\n";

  std::filesystem::path scan_path = input;
  std::filesystem::path temp_repo;

  if (is_git_url(input)) {

    std::cout << "Cloning repository...\n";

    temp_repo = RepoScanner::clone(input);
    scan_path = temp_repo;
  }

  DirectoryScanner scanner;

  auto files = scanner.scan(scan_path);

  if (is_git_url(input)) {

    GitRepositoryReport git_report;

    auto summary = git_report.analyze(files);

    git_report.print(summary);
  }

  if (is_git_url(input)) {

    std::string repo_name = RepoScanner::repository_name(input);

    std::cout << repo_name << "\n";

  } else {

    std::cout << scan_path.filename().string() << "\n";
  }

  scanner.tree(files, scan_path);

  ProjectReport report;
  report.generate(files);

  if (!temp_repo.empty()) {
    RepoScanner::cleanup(temp_repo);
  }
}

} // namespace archaeologist