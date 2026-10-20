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
  Stack s1, s2, s3;
  init(&s1);
  init(&s2);
  init(&s3);

  for (int i = 0; i < 1000; i++) {
    push(&s1, i);
    push(&s2, -i);
  }
  assert(s1.size == 1000);
  assert(s2.size == 1000);
  assert(isEmpty(&s3));
  assert(s1.data != s2.data);

  for (int i = 999; i >= 500; i--) {
    assert(pop(&s1) == i);
  }
  assert(s1.size == 500);
  assert(s2.size == 1000);
  assert(pop(&s2) == -999);

  pop(&s3);
  assert(s3.status == STACK_ERR_EMPTY);
  assert(s1.status == STACK_OK);
  assert(s2.status == STACK_OK);

  destroy(&s1);
  for (int i = 998; i >= 0; i--) {
    assert(pop(&s2) == -i);
  }
  assert(isEmpty(&s2));

  destroy(&s2);
  destroy(&s3);
}

int main() {
  test_empty();
  test_lifo();
  test_pop_empty();
  test_growth();
  test_multiple();
  printf("All tests passed.\n");
  return 0;
}
