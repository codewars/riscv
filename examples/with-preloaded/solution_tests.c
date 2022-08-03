#include <cgreen/cgreen.h>
#include "preloaded.h"

int pascal(int, int);

Describe(Pascal);
BeforeEach(Pascal) {}
AfterEach(Pascal) {}

Ensure(Pascal, works_for_some_fixed_tests) {
  assert_that(pascal(0, 0), is_equal_to(1));
  assert_that(pascal(1, 0), is_equal_to(1));
  assert_that(pascal(1, 1), is_equal_to(1));
  assert_that(pascal(2, 0), is_equal_to(1));
  assert_that(pascal(2, 1), is_equal_to(2));
  assert_that(pascal(2, 2), is_equal_to(1));
  assert_that(pascal(7, 3), is_equal_to(35));
  assert_that(pascal(9, 2), is_equal_to(36));
  assert_that(pascal(8, 4), is_equal_to(70));
}

TestSuite *solution_tests() {
  TestSuite *suite = create_test_suite();
  add_test_with_context(suite, Pascal, works_for_some_fixed_tests);
  return suite;
}
