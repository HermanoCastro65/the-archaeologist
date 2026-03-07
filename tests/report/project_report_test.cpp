#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "archaeologist/report/project_report.h"
#include "archaeologist/scanner/directory_scanner.h"

namespace fs = std::filesystem;

void project_report_generates_summary() {

  std::cout << "Running project_report_generates_summary\n";

  fs::path temp = fs::temp_directory_path() / "archaeologist_report_test";

  fs::create_directories(temp / "src");

  std::ofstream(temp / "src" / "main.cpp");
  std::ofstream(temp / "src" / "util.cpp");
  std::ofstream(temp / "README.md");

  archaeologist::DirectoryScanner scanner;

  auto files = scanner.scan(temp);

  archaeologist::ProjectReport report;

  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  report.generate(files);

  std::cout.rdbuf(old);

  std::string output = buffer.str();

  assert(output.find("Total files") != std::string::npos);
  assert(output.find(".cpp") != std::string::npos);

  fs::remove_all(temp);
}