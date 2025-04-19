
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "concurrency/test_stack_mutex_cond.h"

int main(void) {
  int failures;

  SRunner *sr = srunner_create(stack_suite());

  srunner_run_all(sr, CK_VERBOSE);
  failures = srunner_ntests_failed(sr);

  int run = srunner_ntests_run(sr);
  int failed = srunner_ntests_failed(sr);
  printf("Total: %d run, %d failed\n", run, failed);

  srunner_free(sr);
  return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
