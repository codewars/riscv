#include <cgreen/reporter.h>
#include <cgreen/breadcrumb.h>
#include <stdio.h>

static void codewars_reporter_start_suite(TestReporter *reporter, const char *name, int count) {
  printf("<DESCRIBE::>%s\n", name);
  reporter_start_suite(reporter, name, count);
}

static void codewars_reporter_start_test(TestReporter *reporter, const char *name) {
  printf("<IT::>%s\n", name);
  reporter_start_test(reporter, name);
}

static void codewars_show_pass(TestReporter *reporter, const char *file, int line, const char *message, va_list arguments) {
  printf("<PASSED::>Test Passed\n");
}

static void codewars_show_fail(TestReporter *reporter, const char *file, int line, const char *message, va_list arguments) {
  printf("<FAILED::>");
  vprintf(message, arguments);
  printf("\n");
}

static void codewars_reporter_finish_test(TestReporter *reporter, const char *filename, int line, const char *message) {
  reporter_finish_test(reporter, filename, line, message);
  printf("<COMPLETEDIN::>\n");
}

static void codewars_reporter_finish_suite(TestReporter *reporter, const char *filename, int line) {
  reporter_finish_suite(reporter, filename, line);
  printf("<COMPLETEDIN::>\n");
}

TestReporter *create_codewars_reporter() {
  TestReporter *reporter = create_reporter();
  reporter->start_suite = &codewars_reporter_start_suite;
  reporter->start_test = &codewars_reporter_start_test;
  reporter->show_pass = &codewars_show_pass;
  reporter->show_fail = &codewars_show_fail;
  reporter->finish_test = &codewars_reporter_finish_test;
  reporter->finish_suite = &codewars_reporter_finish_suite;
  return reporter;
}
