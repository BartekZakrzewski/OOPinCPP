#include <assert.h>
#include <stdio.h>

#include "Stack.h"

static void test_empty(void) {
  Stack s;
  init(&s);
  assert(isEmpty(&s));
  assert(s.size == 0);
  destroy(&s);
}

static void test_lifo(void) {
  Stack s;
  init(&s);
  for (int i = 1; i <= 10; i++)
    push(&s, i);
  assert(s.size == 10);
  for (int i = 10; i >= 1; i--)
    assert(pop(&s) == i);
  assert(isEmpty(&s));
  destroy(&s);
}

static void test_pop_empty(void) {
  Stack s;
  init(&s);
  pop(&s);
  assert(s.status == STACK_ERR_EMPTY);
  destroy(&s);
}

static void test_growth(void) {
  Stack s;
  init(&s);
  for (int i = 0; i < 1000; i++)
    push(&s, i);
  assert(s.size == 1000);
  assert(s.capacity >= 1000);
  assert(pop(&s) == 999);
  destroy(&s);
}

int main(void) {
  test_empty();
  test_lifo();
  test_pop_empty();
  test_growth();
  printf("All tests passed.\n");
  return 0;
}
