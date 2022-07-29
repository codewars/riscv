#include <cgreen/cgreen.h>

TestSuite *solution_tests();

int main(int argc, char **argv) {
  TestSuite *suite = create_test_suite();
  add_suite(suite, solution_tests());
  return run_test_suite(suite, create_text_reporter());
}
