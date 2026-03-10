#include "archaeologist/search/file_finder.h"

#include <fstream>
#include <iostream>

namespace archaeologist {

std::vector<std::filesystem::path> FileFinder::find(const std::vector<std::filesystem::path> &files,
                                                    const std::string &filename) {

  std::vector<std::filesystem::path> results;

  for (const auto &file : files) {

    if (file.filename() == filename) {
      results.push_back(file);
    }
  }

  return results;
}

void FileFinder::print_file_content(const std::filesystem::path &path,
                                    const std::filesystem::path &root) {

  std::ifstream file(path);

  if (!file.is_open()) {
    std::cout << "Unable to open file\n";
    return;
  }

  std::filesystem::path relative = std::filesystem::relative(path, root);

  std::cout << "\n========== FILE FOUND ==========\n";
  std::cout << relative.string() << "\n";
  std::cout << "================================\n";
  std::cout << "---- FILE CONTENT ----\n";

  std::string line;

  while (std::getline(file, line)) {
    std::cout << line << "\n";
  }

  std::cout << "----------------------\n";
}

void FileFinder::print_file_content(const std::filesystem::path &path) {

  std::ifstream file(path);

  if (!file.is_open()) {
    std::cout << "Unable to open file\n";
    return;
  }

  std::cout << "\n========== FILE FOUND ==========\n";
  std::cout << path.string() << "\n";
  std::cout << "================================\n";
  std::cout << "---- FILE CONTENT ----\n";

  std::string line;

  while (std::getline(file, line)) {
    std::cout << line << "\n";
  }

  std::cout << "----------------------\n";
}

} // namespace archaeologist