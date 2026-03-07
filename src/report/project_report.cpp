#include "archaeologist/report/project_report.h"

#include <iostream>
#include <map>

namespace archaeologist {

void ProjectReport::generate(const std::vector<std::filesystem::path> &files) {
  std::map<std::string, int> extensions;

  for (const auto &file : files) {
    auto ext = file.extension().string();

    if (ext.empty())
      ext = "(no extension)";

    extensions[ext]++;
  }

  std::cout << "\nProject Report\n";
  std::cout << "==============\n\n";

  std::cout << "Total files: " << files.size() << "\n\n";

  std::cout << "File types\n";
  std::cout << "----------\n";

  for (auto &[ext, count] : extensions) {
    std::cout << ext << " : " << count << "\n";
  }

  std::cout << "\n";
}

} // namespace archaeologist