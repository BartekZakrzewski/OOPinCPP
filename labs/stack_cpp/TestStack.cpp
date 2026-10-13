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

static void fill(Stack &s, int n) {
  for (int i = 1; i <= n; i++) {
    s.push(i);
  }
}

static void test_copy_constructor() {
  Stack a;
  fill(a, 5);
  Stack b(a);
  assert(b.size() == 5);
  assert(b.capacity() == 5);
  b.push(6);
  assert(a.size() == 5);
  assert(b.pop() == 6);
  assert(b.pop() == 5);

  Stack empty;
  Stack c(empty);
  assert(c.isEmpty());
  assert(c.capacity() == 0);
}

static void test_assign() {
  Stack big, small;
  fill(big, 20);
  fill(small, 2);

  Stack s1 = small;
  s1 = big;
  assert(s1.size() == 20);
  assert(s1.pop() == 20);

  Stack s2 = big;
  std::size_t cap = s2.capacity();
  s2 = small;
  assert(s2.capacity() == cap);
  assert(s2.size() == 2);
  assert(s2.pop() == 2);

  Stack s3, empty;
  s3 = empty;
  assert(s3.isEmpty());

  Stack &ref = big;
  big = ref;
  assert(big.size() == 20);
  assert(big.pop() == 20);
}

static void runSomeFunction(Stack s) { s.push(99); }

static void runAnotherFunction(Stack &s) { s.push(99); }

static void test_debugger_scenario() {
  Stack s1;
  s1.push(1);
  s1.push(2);
  s1.push(3);

  Stack s2(s1);

  Stack s3 = s1;

  Stack s4;
  s4.push(10);
  s4 = s1;

  runSomeFunction(s1);
  assert(s1.size() == 3);
  runAnotherFunction(s1);
  assert(s1.size() == 4);
}

int main() {
  test_empty();
  test_lifo();
  test_pop_empty();
  test_growth();
  test_copy_constructor();
  test_assign();
  // test_debugger_scenario();
  std::printf("All tests passed.\n");
  return 0;
}
