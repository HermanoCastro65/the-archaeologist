#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "archaeologist/search/file_finder.h"

void file_finder_prints_file_content() {

  std::filesystem::create_directories("test_repo");

  std::ofstream file("test_repo/example.txt");
  file << "hello archaeologist";
  file.close();

  archaeologist::FileFinder finder;

  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  finder.print_file_content("test_repo/example.txt");

  std::cout.rdbuf(old);

  std::string output = buffer.str();

  if (output.find("hello archaeologist") == std::string::npos) {
    throw std::runtime_error("File content not printed correctly");
  }

  std::filesystem::remove_all("test_repo");
}