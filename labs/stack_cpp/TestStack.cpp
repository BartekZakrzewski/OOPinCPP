#include <cassert>
#include <cstdio>

#include "Stack.h"

static void test_empty() {
  Stack s;
  assert(s.isEmpty());
  assert(s.size() == 0);
}

static void test_lifo() {
  Stack s;
  for (int i = 1; i <= 10; i++)
    s.push(i);
  assert(s.size() == 10);
  for (int i = 10; i >= 1; i--)
    assert(s.pop() == i);
  assert(s.isEmpty());
}

static void test_pop_empty() {
  Stack s;
  s.pop();
  assert(s.status() == Status::Empty);
}

static void test_growth() {
  Stack s;
  for (int i = 0; i < 1000; i++)
    s.push(i);
  assert(s.size() == 1000);
  assert(s.capacity() >= 1000);
  assert(s.pop() == 999);
}

int main() {
  test_empty();
  test_lifo();
  test_pop_empty();
  test_growth();
  std::printf("All tests passed.\n");
  return 0;
}
