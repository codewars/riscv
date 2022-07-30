#include <cgreen/cgreen.h>

TestSuite *solution_tests();
TestReporter *create_codewars_reporter();

int main(int argc, char **argv) {
  TestSuite *suite = create_test_suite();
  add_suite(suite, solution_tests());
  return run_test_suite(suite, create_codewars_reporter());
}
