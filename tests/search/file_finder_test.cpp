#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "archaeologist/search/file_finder.h"

void file_finder_locates_file() {

  std::filesystem::create_directories("test_repo");

  std::ofstream file("test_repo/test_file.txt");
  file << "hello archaeologist";
  file.close();

  std::vector<std::filesystem::path> files = {"test_repo/test_file.txt"};

  archaeologist::FileFinder finder;

  auto result = finder.find(files, "test_file.txt");

  if (result.empty()) {
    throw std::runtime_error("File was not found");
  }

  std::filesystem::remove_all("test_repo");
}