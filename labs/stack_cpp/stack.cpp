#include "stack.h"
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <utility>

template <typename T> Stack<T>::Stack() {
  size = 0;
  capacity = 0;
  data = malloc(INITIAL_SIZE * sizeof(int));
  if (data == NULL)
    return;
  capacity = INITIAL_SIZE;
}

template <typename T> Stack<T>::~Stack() {
  free(data);
  size = 0;
  capacity = 0;
}

template <typename T> void Stack<T>::push(int element) {
  if (size == capacity && !expand())
    return;
  data[size++] = element;
}

template <typename T> int Stack<T>::pop() {
  if (size <= 0)
    return 0;
  return data[size--];
}

template <typename T> bool Stack<T>::isEmpty() const noexcept {
  return size <= 0;
}

template <typename T> bool Stack<T>::expand() {
  size_t new_cap;
  if (capacity == 0)
    new_cap = INITIAL_SIZE;
  else {
    if (capacity > SIZE_MAX / 2)
      return false;
    new_cap = capacity * GROWTH_SIZE;
  }
  if (new_cap > SIZE_MAX / sizeof(int))
    return false;
  int *tmp = realloc(data, new_cap * sizeof(int));
  if (tmp == NULL)
    return false;
  data = tmp;
  capacity = new_cap;
  return true;
}

// Task 3

template <typename T> Stack<T>::Stack(const Stack &copy) {}

template <typename T> Stack<T> &Stack<T>::operator=(Stack other) noexcept {
  swap(other);
  return *this;
}

template <typename T> void Stack<T>::swap(Stack &other) noexcept {
  std::swap(data, other.data);
  std::swap(size, other.size);
  std::swap(capacity, other.capacity);
}
