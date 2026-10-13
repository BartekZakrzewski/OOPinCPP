#include <cassert>
#include <climits>
#include <cstdio>

#include "Stack.h"
#include "Stack.h"

static int tests_run = 0;

#define RUN(test)                                                              \
  do {                                                                         \
    std::printf("%-45s", #test);                                               \
    test();                                                                    \
    std::printf("OK\n");                                                       \
    tests_run++;                                                               \
  } while (0)

static void test_constructor_gives_empty_stack() {
  Stack s;
  assert(s.status() == Status::Ok);
  assert(s.isEmpty());
  assert(s.size() == 0);
  assert(s.capacity() >= 1);
}

static void test_push_then_pop_single() {
  Stack s;
  s.push(42);
  assert(!s.isEmpty());
  assert(s.pop() == 42);
  assert(s.isEmpty());
  assert(s.status() == Status::Ok);
}

static void test_lifo_order() {
  Stack s;
  for (int i = 1; i <= 5; i++)
    s.push(i);
  for (int i = 5; i >= 1; i--)
    assert(s.pop() == i);
  assert(s.isEmpty());
}

static void test_growth_beyond_initial_capacity() {
  Stack s;
  std::size_t initial = s.capacity();
  const int N = 100000;
  for (int i = 0; i < N; i++) {
    s.push(i);
    assert(s.status() == Status::Ok);
  }
  assert(s.size() == static_cast<std::size_t>(N));
  assert(s.capacity() > initial);
  for (int i = N - 1; i >= 0; i--)
    assert(s.pop() == i);
  assert(s.isEmpty());
}

static void test_growth_is_geometric() {
  Stack s;
  int growths = 0;
  std::size_t last_cap = s.capacity();
  for (int i = 0; i < 100000; i++) {
    s.push(i);
    if (s.capacity() != last_cap) {
      growths++;
      last_cap = s.capacity();
    }
  }
  assert(growths < 30);
}

static void test_pop_on_empty_reports_error() {
  Stack s;
  (void)s.pop();
  assert(s.status() == Status::Empty);
  assert(s.isEmpty());

  s.push(7);
  assert(s.status() == Status::Ok);
  assert(s.pop() == 7);
  assert(s.status() == Status::Ok);

  s.push(1);
  s.pop();
  (void)s.pop();
  assert(s.status() == Status::Empty);
}

static void test_extreme_values() {
  Stack s;
  s.push(INT_MAX);
  s.push(INT_MIN);
  s.push(0);
  s.push(-1);
  assert(s.pop() == -1);
  assert(s.pop() == 0);
  assert(s.pop() == INT_MIN);
  assert(s.pop() == INT_MAX);
}

static void test_interleaved_push_pop() {
  Stack s;
  for (int round = 0; round < 1000; round++) {
    s.push(round);
    s.push(round + 1);
    assert(s.pop() == round + 1);
  }
  assert(s.size() == 1000);
  for (int round = 999; round >= 0; round--)
    assert(s.pop() == round);
  assert(s.isEmpty());
}

static void test_many_stacks_in_scope() {
  for (int i = 0; i < 100; i++) {
    Stack a;
    Stack b;
    for (int j = 0; j < i; j++) {
      a.push(j);
      b.push(-j);
    }
    assert(a.size() == static_cast<std::size_t>(i));
    assert(b.size() == static_cast<std::size_t>(i));
  }
}

static void test_heap_allocated_stack() {
  Stack *s = new Stack;
  s->push(3);
  s->push(4);
  assert(s->pop() == 4);
  delete s;
}

int main() {
  RUN(test_constructor_gives_empty_stack);
  RUN(test_push_then_pop_single);
  RUN(test_lifo_order);
  RUN(test_growth_beyond_initial_capacity);
  RUN(test_growth_is_geometric);
  RUN(test_pop_on_empty_reports_error);
  RUN(test_extreme_values);
  RUN(test_interleaved_push_pop);
  RUN(test_many_stacks_in_scope);
  RUN(test_heap_allocated_stack);

  std::printf("\nAll %d tests passed.\n", tests_run);
  return 0;
}
