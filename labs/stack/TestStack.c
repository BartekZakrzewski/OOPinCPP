#include <assert.h>
#include <stdio.h>

#include "Stack.h"

void test_empty() {
  Stack s;
  init(&s);
  assert(isEmpty(&s));
  assert(s.size == 0);
  destroy(&s);
}

void test_lifo() {
  Stack s;
  init(&s);
  for (int i = 1; i <= 10; i++) {
    push(&s, i);
  }
  assert(s.size == 10);
  for (int i = 10; i >= 1; i--) {
    assert(pop(&s) == i);
  }
  assert(isEmpty(&s));
  destroy(&s);
}

void test_pop_empty() {
  Stack s;
  init(&s);
  pop(&s);
  assert(s.status == STACK_ERR_EMPTY);
  destroy(&s);
}

void test_growth() {
  Stack s;
  init(&s);
  for (int i = 0; i < 1000; i++) {
    push(&s, i);
  }
  assert(s.size == 1000);
  assert(s.capacity >= 1000);
  assert(pop(&s) == 999);
  destroy(&s);
}

void test_multiple() {
  Stack s1, s2;
  init(&s1);
  init(&s2);
  for (int i = 0; i < 1000; i++) {
    push(&s1, i);
  }
  for (int i = 0; i < 1000; i++) {
    push(&s2, i);
  }
  assert(s1.size == 1000);
}

int main() {
  test_empty();
  test_lifo();
  test_pop_empty();
  test_growth();
  printf("All tests passed.\n");
  return 0;
}
