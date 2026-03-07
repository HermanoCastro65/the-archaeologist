#include "test_runner.h"

void basic_test();
void build_artifact_test();
void directory_scanner_lists_files();
void directory_scanner_list_outputs_files();
void self_runner_scans_project();

int main() {
  run_test("basic_test", basic_test);
  run_test("build_artifact_test", build_artifact_test);
  run_test("directory_scanner_lists_files", directory_scanner_lists_files);
  run_test("directory_scanner_list_outputs_files", directory_scanner_list_outputs_files);
  run_test("self_runner_scans_project", self_runner_scans_project);

  print_summary();

  return 0;
}