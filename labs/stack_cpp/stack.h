#pragma once

#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <utility>

#define INITIAL_SIZE 4
#define GROWTH_SIZE 2

template <typename T> class Stack {
public:
  Stack();
  ~Stack();
  void push(int element);
  int pop();
  bool isEmpty() const noexcept;
  // Task 3
  Stack(const Stack &copy);
  Stack &operator=(Stack other) noexcept;

private:
  T *data;
  std::size_t size;
  std::size_t capacity;
  bool expand();
  // Task 3
  void swap(Stack &other) noexcept;
};
