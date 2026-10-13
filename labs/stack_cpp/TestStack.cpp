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

static Stack make_stack(int from, int to) {
  Stack s;
  for (int i = from; i <= to; i++) {
    s.push(i);
  }
  return s;
}

static void assert_contents(Stack s, int from, int to) {
  assert(s.size() == static_cast<std::size_t>(to - from + 1));
  for (int i = to; i >= from; i--) {
    assert(s.pop() == i);
  }
  assert(s.isEmpty());
}

static void test_copy_ctor() {
  Stack a = make_stack(1, 5);
  Stack b(a);
  assert(b.status() == Status::Ok);
  assert(b.size() == 5);
  assert(b.capacity() == 5);
  assert_contents(b, 1, 5);
  assert_contents(a, 1, 5);
}

static void test_copy_ctor_empty() {
  Stack a;
  Stack b(a);
  assert(b.isEmpty());
  assert(b.capacity() == 0);
  b.push(42);
  assert(b.pop() == 42);
}

static void test_copy_independent() {
  Stack a = make_stack(1, 3);
  Stack b(a);
  b.push(4);
  a.pop();
  assert_contents(a, 1, 2);
  assert_contents(b, 1, 4);
}

static void test_assign_larger_to_smaller() {
  Stack big = make_stack(1, 20);
  Stack small = make_stack(100, 101);
  small = big;
  assert(small.capacity() >= 20);
  assert_contents(small, 1, 20);
  assert_contents(big, 1, 20);
}

static void test_assign_smaller_to_larger() {
  Stack big = make_stack(1, 20);
  Stack small = make_stack(100, 101);
  std::size_t cap = big.capacity();
  big = small;
  assert(big.capacity() == cap);
  assert_contents(big, 100, 101);
}

static void test_assign_equal_size() {
  Stack a = make_stack(1, 4);
  Stack b = make_stack(5, 8);
  std::size_t cap = a.capacity();
  a = b;
  assert(a.capacity() == cap);
  assert_contents(a, 5, 8);
}

static void test_assign_empty() {
  Stack a = make_stack(1, 4);
  Stack empty;
  a = empty;
  assert(a.isEmpty());
  a.push(7);
  assert(a.pop() == 7);

  Stack b;
  b = make_stack(1, 3);
  assert_contents(b, 1, 3);
}

static void test_assign_from_zero_capacity() {
  Stack empty;
  Stack zero(empty);
  zero = make_stack(1, 6);
  assert_contents(zero, 1, 6);
}

static void test_self_assign() {
  Stack a = make_stack(1, 5);
  Stack &ref = a;
  a = ref;
  assert_contents(a, 1, 5);
}

static void test_chained_assign() {
  Stack a, b;
  Stack c = make_stack(1, 3);
  a = b = c;
  assert_contents(a, 1, 3);
  assert_contents(b, 1, 3);
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

  assert_contents(s2, 1, 3);
  assert_contents(s3, 1, 3);
  assert_contents(s4, 1, 3);
}

int main() {
  test_empty();
  test_lifo();
  test_pop_empty();
  test_growth();
  test_copy_ctor();
  test_copy_ctor_empty();
  test_copy_independent();
  test_assign_larger_to_smaller();
  test_assign_smaller_to_larger();
  test_assign_equal_size();
  test_assign_empty();
  test_assign_from_zero_capacity();
  test_self_assign();
  test_chained_assign();
  test_debugger_scenario();
  std::printf("All tests passed.\n");
  return 0;
}
