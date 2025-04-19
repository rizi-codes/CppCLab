#include "concurrency/test_stack_mutex_cond.h"
#include "concurrency/stack_mutex_cond.h"
#include <check.h>
#include <pthread.h>
#include <unistd.h>

START_TEST(test_try_pop_empty) {
  Stack s;
  ck_assert_int_eq(stack_init(&s, sizeof(int)), 0);
  int v = 0;
  ck_assert(!stack_try_pop(&s, &v));
  stack_destroy(&s);
}
END_TEST

Suite *stack_suite(void) {
  Suite *s = suite_create("StackMutexCond");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_try_pop_empty);
  suite_add_tcase(s, tc);
  return s;
}
