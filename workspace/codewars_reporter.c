#include <cgreen/reporter.h>
#include <cgreen/breadcrumb.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct ts_node {
  clock_t ts;
  struct ts_node *next;
};

const char *CODEWARS_LF = "<:LF:>";

static void push_ts(struct ts_node **memo) {
  if (memo == NULL)
    return;
  struct ts_node *head = malloc(sizeof(struct ts_node));
  head->ts = clock();
  head->next = *memo;
  *memo = head;
}

static clock_t pop_ts(struct ts_node **memo) {
  if (memo == NULL || *memo == NULL)
    return -1;
  clock_t ts = (*memo)->ts;
  struct ts_node *tail = (*memo)->next;
  free(*memo);
  *memo = tail;
  return ts;
}

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
  push_ts((struct ts_node **)&reporter->memo);
}

static void codewars_reporter_start_test(TestReporter *reporter, const char *name) {
  printf("\n<IT::>%s\n", name);
  reporter_start_test(reporter, name);
  reporter->passes = 0;
  reporter->failures = 0;
  reporter->skips = 0;
  reporter->exceptions = 0;
  push_ts((struct ts_node **)&reporter->memo);
}

static void codewars_reporter_show_pass(TestReporter *reporter, const char *file, int line, const char *message, va_list arguments) {
  printf("\n<PASSED::>Test Passed\n");
}

static void codewars_reporter_show_fail(TestReporter *reporter, const char *file, int line, const char *message, va_list arguments) {
  printf("\n<FAILED::>");
  char *escaped_message = create_codewars_escape_message(message);
  vprintf(escaped_message, arguments);
  free(escaped_message);
  printf("\n");
}

static void codewars_reporter_finish_test(TestReporter *reporter, const char *filename, int line, const char *message) {
  clock_t ts_diff = clock() - pop_ts((struct ts_node **)&reporter->memo);
  // This function increments passes/failures counts.
  reporter_finish_test(reporter, filename, line, message);
  // Increment the totals. `total_failures` is used to determine the exit code.
  reporter->total_passes += reporter->passes;
  reporter->total_failures += reporter->failures;
  reporter->total_skips += reporter->skips;
  reporter->total_exceptions += reporter->exceptions;
  printf("\n<COMPLETEDIN::>%ld\n", 1000 * ts_diff / CLOCKS_PER_SEC);
}

static void codewars_reporter_finish_suite(TestReporter *reporter, const char *filename, int line) {
  clock_t ts_diff = clock() - pop_ts((struct ts_node **)&reporter->memo);
  reporter_finish_suite(reporter, filename, line);
  printf("\n<COMPLETEDIN::>%ld\n", 1000 * ts_diff / CLOCKS_PER_SEC);
}

TestReporter *create_codewars_reporter() {
  TestReporter *reporter = create_reporter();
  reporter->start_suite = &codewars_reporter_start_suite;
  reporter->start_test = &codewars_reporter_start_test;
  reporter->show_pass = &codewars_reporter_show_pass;
  reporter->show_fail = &codewars_reporter_show_fail;
  reporter->finish_test = &codewars_reporter_finish_test;
  reporter->finish_suite = &codewars_reporter_finish_suite;
  reporter->memo = NULL;
  return reporter;
}
