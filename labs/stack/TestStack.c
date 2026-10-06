#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "Stack.h"

static int tests_run = 0;

#define RUN(test)                                                              \
  do {                                                                         \
    printf("%-45s", #test);                                                    \
    test();                                                                    \
    printf("OK\n");                                                            \
    tests_run++;                                                               \
  } while (0)

static void test_init_gives_empty_stack(void) {
  Stack s;
  init(&s);
  assert(s.status == STACK_OK);
  assert(isEmpty(&s));
  assert(s.size == 0);
  assert(s.capacity >= 1);
  destroy(&s);
}

static void test_push_then_pop_single(void) {
  Stack s;
  init(&s);
  push(&s, 42);
  assert(!isEmpty(&s));
  assert(pop(&s) == 42);
  assert(isEmpty(&s));
  assert(s.status == STACK_OK);
  destroy(&s);
}

static void test_lifo_order(void) {
  Stack s;
  init(&s);
  for (int i = 1; i <= 5; i++)
    push(&s, i);
  for (int i = 5; i >= 1; i--)
    assert(pop(&s) == i);
  assert(isEmpty(&s));
  destroy(&s);
}

static void test_growth_beyond_initial_capacity(void) {
  Stack s;
  init(&s);
  size_t initial = s.capacity;
  const int N = 100000;
  for (int i = 0; i < N; i++) {
    push(&s, i);
    assert(s.status == STACK_OK);
  }
  assert(s.size == (size_t)N);
  assert(s.capacity > initial);
  for (int i = N - 1; i >= 0; i--)
    assert(pop(&s) == i);
  assert(isEmpty(&s));
  destroy(&s);
}

static void test_growth_is_geometric(void) {
  /* Count reallocations: with doubling, 100000 pushes need ~15 growths,
     with +1 growth they would need ~100000. */
  Stack s;
  init(&s);
  int growths = 0;
  size_t last_cap = s.capacity;
  for (int i = 0; i < 100000; i++) {
    push(&s, i);
    if (s.capacity != last_cap) {
      growths++;
      last_cap = s.capacity;
    }
  }
  assert(growths < 30);
  destroy(&s);
}

static void test_pop_on_empty_reports_error(void) {
  Stack s;
  init(&s);
  (void)pop(&s);
  assert(s.status == STACK_ERR_EMPTY);
  assert(isEmpty(&s));

  /* The stack must remain usable after the error. */
  push(&s, 7);
  assert(s.status == STACK_OK);
  assert(pop(&s) == 7);
  assert(s.status == STACK_OK);

  /* Pop until empty, then once more. */
  push(&s, 1);
  pop(&s);
  (void)pop(&s);
  assert(s.status == STACK_ERR_EMPTY);
  destroy(&s);
}

static void test_extreme_values(void) {
  Stack s;
  init(&s);
  push(&s, INT_MAX);
  push(&s, INT_MIN);
  push(&s, 0);
  push(&s, -1);
  assert(pop(&s) == -1);
  assert(pop(&s) == 0);
  assert(pop(&s) == INT_MIN);
  assert(pop(&s) == INT_MAX);
  destroy(&s);
}

static void test_interleaved_push_pop(void) {
  Stack s;
  init(&s);
  for (int round = 0; round < 1000; round++) {
    push(&s, round);
    push(&s, round + 1);
    assert(pop(&s) == round + 1);
  }
  assert(s.size == 1000);
  for (int round = 999; round >= 0; round--)
    assert(pop(&s) == round);
  assert(isEmpty(&s));
  destroy(&s);
}

static void test_reuse_after_destroy(void) {
  Stack s;
  init(&s);
  push(&s, 1);
  destroy(&s);
  assert(isEmpty(&s));
  assert(s.data == NULL);

  init(&s);
  push(&s, 2);
  assert(pop(&s) == 2);
  destroy(&s);
}

static void test_double_destroy_and_null_safety(void) {
  Stack s;
  init(&s);
  push(&s, 1);
  destroy(&s);
  destroy(&s);   /* must not crash or double free */
  destroy(NULL); /* must not crash */
  assert(isEmpty(NULL));
}

static void test_push_on_stack_without_buffer(void) {
  /* Simulates a stack whose init allocation failed: data == NULL,
     capacity == 0. push must recover by allocating. */
  Stack s = {NULL, 0, 0, STACK_ERR_ALLOC};
  push(&s, 5);
  assert(s.status == STACK_OK);
  assert(pop(&s) == 5);
  destroy(&s);
}

static void test_allocation_failure_is_reported(void) {
  /* Pretend the stack is full with a huge capacity so that growing it
     overflows size_t. push must fail cleanly, without touching memory. */
  Stack s;
  init(&s);
  push(&s, 1);

  int *real_data = s.data;
  size_t real_cap = s.capacity;
  size_t real_size = s.size;

  s.capacity = SIZE_MAX / sizeof(int);
  s.size = s.capacity;
  push(&s, 2);
  assert(s.status == STACK_ERR_ALLOC);
  assert(s.size == SIZE_MAX / sizeof(int)); /* unchanged */
  assert(s.data == real_data);              /* buffer untouched */

  /* Restore the real state so destroy/valgrind see consistent data. */
  s.capacity = real_cap;
  s.size = real_size;
  assert(pop(&s) == 1);
  destroy(&s);
}

int main(void) {
  RUN(test_init_gives_empty_stack);
  RUN(test_push_then_pop_single);
  RUN(test_lifo_order);
  RUN(test_growth_beyond_initial_capacity);
  RUN(test_growth_is_geometric);
  RUN(test_pop_on_empty_reports_error);
  RUN(test_extreme_values);
  RUN(test_interleaved_push_pop);
  RUN(test_reuse_after_destroy);
  RUN(test_double_destroy_and_null_safety);
  RUN(test_push_on_stack_without_buffer);
  RUN(test_allocation_failure_is_reported);

  printf("\nAll %d tests passed.\n", tests_run);
  return 0;
}
