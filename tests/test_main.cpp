#include "test_runner.h"

void basic_test();
void build_artifact_test();
void directory_scanner_lists_files();
void directory_scanner_list_outputs_files();

int main() {
  run_test("basic_test", basic_test);
  run_test("build_artifact_test", build_artifact_test);
  run_test("directory_scanner_lists_files", directory_scanner_lists_files);
  run_test("directory_scanner_list_outputs_files", directory_scanner_list_outputs_files);

  print_summary();

  return 0;
}