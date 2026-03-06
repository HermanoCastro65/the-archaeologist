#include "test_runner.h"

void basic_test();
void build_artifact_test();
void directory_scanner_lists_files();

int main() {
  run_test("basic_test", basic_test);
  run_test("build_artifact_test", build_artifact_test);
  run_test("directory_scanner_lists_files", directory_scanner_lists_files);

  print_summary();

  return 0;
}