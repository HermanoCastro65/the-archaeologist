#include "archaeologist/runner/self_runner.h"
#include "archaeologist/report/project_report.h"
#include "archaeologist/scanner/directory_scanner.h"

#include <iostream>

namespace archaeologist {

void SelfRunner::run(const std::string &path) {

  std::cout << "\nRunning Archaeologist self-runner...\n";
  std::cout << "Scanning project: " << path << "\n\n";

  DirectoryScanner scanner;

  auto files = scanner.scan(path);

  scanner.tree(files);

  ProjectReport report;

  report.generate(files);
}

} // namespace archaeologist