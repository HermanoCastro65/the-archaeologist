#include <filesystem>
#include <stdexcept>
#include <vector>

#include "archaeologist/report/git_repository_report.h"

void git_repository_report_generates_summary() {

  std::vector<std::filesystem::path> files = {"repo/src/main.cpp", "repo/src/engine.cpp",
                                              "repo/include/engine.h", "repo/core/node.cpp",
                                              "repo/editor/editor.cpp"};

  archaeologist::GitRepositoryReport report;

  auto summary = report.analyze(files);

  if (summary.files != 5) {
    throw std::runtime_error("Incorrect file count");
  }

  if (summary.directories == 0) {
    throw std::runtime_error("Directories not detected");
  }

  if (summary.language.empty()) {
    throw std::runtime_error("Language detection failed");
  }
}