#include "archaeologist/report/git_repository_report.h"

#include <iostream>
#include <map>
#include <set>

namespace archaeologist {

static std::string detect_language(const std::map<std::string, int> &ext) {

  if (ext.count(".cpp") || ext.count(".hpp") || ext.count(".h"))
    return "C++";

  if (ext.count(".py"))
    return "Python";

  if (ext.count(".js"))
    return "JavaScript";

  return "Unknown";
}

GitRepositorySummary GitRepositoryReport::analyze(const std::vector<std::filesystem::path> &files) {

  std::map<std::string, int> extensions;
  std::set<std::string> directories;

  for (const auto &file : files) {

    auto ext = file.extension().string();
    extensions[ext]++;

    directories.insert(file.parent_path().string());
  }

  GitRepositorySummary summary;

  summary.files = files.size();
  summary.directories = directories.size();
  summary.language = detect_language(extensions);

  return summary;
}

void GitRepositoryReport::print(const GitRepositorySummary &summary) {

  std::cout << "\nRepository Report\n";
  std::cout << "=================\n\n";

  std::cout << "Language: " << summary.language << "\n";
  std::cout << "Files: " << summary.files << "\n";
  std::cout << "Directories: " << summary.directories << "\n\n";
}

} // namespace archaeologist