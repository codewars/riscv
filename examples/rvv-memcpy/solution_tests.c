#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <cgreen/cgreen.h>

void *rvv_memcpy(void *dst, const void *src, size_t len);

Describe(rvv_memcpy);
BeforeEach(rvv_memcpy) {}
AfterEach(rvv_memcpy) {}

Ensure(rvv_memcpy, works_for_some_fixed_tests) {
  char buf1[] = "Hello, world!";
  char buf2[] = "Alhoa, RISC-V!";
  char *res = rvv_memcpy(buf2, buf1, 5);
  assert_that(res, is_equal_to(buf2));
  assert_that(buf2, is_equal_to_string("Hello, RISC-V!"));
}

TestSuite *solution_tests() {
  TestSuite *suite = create_test_suite();
  add_test_with_context(suite, rvv_memcpy, works_for_some_fixed_tests);
  return suite;
}
