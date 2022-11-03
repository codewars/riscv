#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <cgreen/cgreen.h>

uint32_t sha256_sigma0(uint32_t input);

uint32_t sha256_sigma0_ref(uint32_t input) {
  uint32_t a = (input >> 7) | (input << 25);
  uint32_t b = (input >> 18) | (input << 14);
  uint32_t c = input >> 3;
  return a ^ b ^ c;
}

Describe(sha256_sigma0);
BeforeEach(sha256_sigma0) {}
AfterEach(sha256_sigma0) {}

Ensure(sha256_sigma0, works_for_some_fixed_tests) {
  assert_that(sha256_sigma0(0x12345678u), is_equal_to(sha256_sigma0_ref(0x12345678)));
}

TestSuite *solution_tests() {
  TestSuite *suite = create_test_suite();
  add_test_with_context(suite, sha256_sigma0, works_for_some_fixed_tests);
  return suite;
}
