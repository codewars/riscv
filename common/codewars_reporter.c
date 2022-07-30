#include <cgreen/reporter.h>
#include <cgreen/breadcrumb.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const char *CODEWARS_LF = "<:LF:>";

static char *create_codewars_escape_message(const char *message) {
  size_t msglen = 0;
  const size_t LF_LEN = strlen(CODEWARS_LF);
  const char *tmp = message;
  while (*tmp) {
    msglen += *tmp == '\n' ? LF_LEN : 1;
    ++tmp;
  }
  char *escaped_message = calloc(msglen + 1, sizeof(char));
  if (escaped_message == NULL) {
    fprintf(stderr, "Call to calloc() failed: insufficient memory; exiting\n");
    exit(EXIT_FAILURE);
  }
  char buf[2];
  buf[1] = '\0';
  while (*message) {
    if (*message == '\n') {
      strcat(escaped_message, CODEWARS_LF);
    } else {
      buf[0] = *message;
      strcat(escaped_message, buf);
    }
    ++message;
  }
  return escaped_message;
}

static void codewars_reporter_start_suite(TestReporter *reporter, const char *name, int count) {
  printf("\n<DESCRIBE::>%s\n", name);
  reporter_start_suite(reporter, name, count);
}

static void codewars_reporter_start_test(TestReporter *reporter, const char *name) {
  printf("\n<IT::>%s\n", name);
  reporter_start_test(reporter, name);
}

static void codewars_show_pass(TestReporter *reporter, const char *file, int line, const char *message, va_list arguments) {
  printf("\n<PASSED::>Test Passed\n");
}

static void codewars_show_fail(TestReporter *reporter, const char *file, int line, const char *message, va_list arguments) {
  printf("\n<FAILED::>");
  char *escaped_message = create_codewars_escape_message(message);
  vprintf(escaped_message, arguments);
  free(escaped_message);
  printf("\n");
}

static void codewars_reporter_finish_test(TestReporter *reporter, const char *filename, int line, const char *message) {
  reporter_finish_test(reporter, filename, line, message);
  printf("\n<COMPLETEDIN::>\n");
}

static void codewars_reporter_finish_suite(TestReporter *reporter, const char *filename, int line) {
  reporter_finish_suite(reporter, filename, line);
  printf("\n<COMPLETEDIN::>\n");
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
