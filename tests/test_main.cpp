#include "test_runner.h"

void basic_test();
void build_artifact_test();

int main() {
  run_test("basic_test", basic_test);
  run_test("build_artifact_test", build_artifact_test);

  print_summary();

  return 0;
}