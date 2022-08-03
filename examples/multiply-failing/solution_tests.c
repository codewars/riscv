#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <cgreen/cgreen.h>

int multiply(int, int);

Describe(Multiply);
BeforeEach(Multiply) {}
AfterEach(Multiply) {}

Ensure(Multiply, missing_assertion) {
}

Ensure(Multiply, works_for_some_fixed_tests) {
  assert_that(multiply(3, 5), is_equal_to(15));
  assert_that(multiply(5, 3), is_equal_to(15));
  assert_that(multiply(2, 2), is_equal_to(4));
  assert_that(multiply(-9, 7), is_equal_to(-63));
  assert_that(multiply(8, -11), is_equal_to(-88));
  assert_that(multiply(-15, -12), is_equal_to(180));
}

Ensure(Multiply, works_for_100_random_tests) {
  srand(time(NULL));
  for (int i = 0; i < 100; ++i) {
    int a = rand() % 100;
    int b = rand() % 100;
    int expected = a * b;
    // assert_that(multiply(a, b), is_equal_to(expected));
    assert_equal_with_message(multiply(a, b), expected, "multiply(%d, %d) == %d", a, b, expected);
  }
}

TestSuite *solution_tests() {
  TestSuite *suite = create_test_suite();
  add_test_with_context(suite, Multiply, missing_assertion);
  add_test_with_context(suite, Multiply, works_for_some_fixed_tests);
  add_test_with_context(suite, Multiply, works_for_100_random_tests);
  return suite;
}
