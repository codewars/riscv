#include <cgreen/cgreen.h>

TestSuite *solution_tests();
TestReporter *create_codewars_reporter();

int main(int argc, char **argv) {
  return run_test_suite(solution_tests(), create_codewars_reporter());
}
