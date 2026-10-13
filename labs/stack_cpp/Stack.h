#pragma once

#include <cstddef>

enum class Status { Ok, AllocError, Empty };

class Stack {
public:
  Stack();
  ~Stack();

  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  void push(int element);
  int pop();
  bool isEmpty() const noexcept;

  Status status() const noexcept;
  std::size_t size() const noexcept;
  std::size_t capacity() const noexcept;

private:
  static constexpr std::size_t INITIAL_CAPACITY = 4;
  static constexpr std::size_t GROWTH_FACTOR = 2;

  int *data_;
  std::size_t size_;
  std::size_t capacity_;
  Status status_;

  bool expand();
};
