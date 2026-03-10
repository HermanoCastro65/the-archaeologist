#include "tests/test_runner.h"

void basic_test();
void build_artifact_test();
void directory_scanner_lists_files();
void directory_scanner_list_outputs_files();
void self_runner_scans_project();
void directory_scanner_ignores_build_and_git();
void directory_scanner_tree_list();
void project_report_generates_summary();
void scanner_respects_ignore_config();
void git_repository_clone_and_cleanup();
void git_repository_report_generates_summary();
void tree_starts_from_repository_root();
void repository_name_extracted_from_url();
void invalid_git_repository_detection();
void git_repository_validation();

int main() {
  run_test("basic_test", basic_test);
  run_test("build_artifact_test", build_artifact_test);
  run_test("directory_scanner_lists_files", directory_scanner_lists_files);
  run_test("directory_scanner_list_outputs_files", directory_scanner_list_outputs_files);
  run_test("self_runner_scans_project", self_runner_scans_project);
  run_test("directory_scanner_ignores_build_and_git", directory_scanner_ignores_build_and_git);
  run_test("directory_scanner_tree_list", directory_scanner_tree_list);
  run_test("project_report_generates_summary", project_report_generates_summary);
  run_test("scanner_respects_ignore_config", scanner_respects_ignore_config);
  run_test("git_repository_clone_and_cleanup", git_repository_clone_and_cleanup);
  run_test("git_repository_report_generates_summary", git_repository_report_generates_summary);
  run_test("tree_starts_from_repository_root", tree_starts_from_repository_root);
  run_test("repository_name_extracted_from_url", repository_name_extracted_from_url);
  run_test("invalid_git_repository_detection", invalid_git_repository_detection);
  run_test("git_repository_validation", git_repository_validation);

  print_summary();

  return 0;
}