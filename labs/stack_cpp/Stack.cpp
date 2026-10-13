#include "Stack.h"

#include <cstdint>
#include <cstdlib>

Stack::Stack() : data_(nullptr), size_(0), capacity_(0), status_(Status::Ok) {
  data_ = static_cast<int *>(std::malloc(INITIAL_CAPACITY * sizeof(int)));
  if (data_ == nullptr) {
    status_ = Status::AllocError;
    return;
  }
  capacity_ = INITIAL_CAPACITY;
}

Stack::~Stack() { std::free(data_); }

bool Stack::expand() {
  std::size_t new_cap;
  if (capacity_ == 0)
    new_cap = INITIAL_CAPACITY;
  else {
    if (capacity_ > SIZE_MAX / GROWTH_FACTOR) {
      status_ = Status::AllocError;
      return false;
    }
    new_cap = capacity_ * GROWTH_FACTOR;
  }
  if (new_cap > SIZE_MAX / sizeof(int)) {
    status_ = Status::AllocError;
    return false;
  }

  int *tmp = static_cast<int *>(std::realloc(data_, new_cap * sizeof(int)));
  if (tmp == nullptr) {
    status_ = Status::AllocError;
    return false;
  }

  data_ = tmp;
  capacity_ = new_cap;
  return true;
}

void Stack::push(int element) {
  if (size_ == capacity_ && !expand())
    return;
  data_[size_++] = element;
  status_ = Status::Ok;
}

int Stack::pop() {
  if (size_ == 0) {
    status_ = Status::Empty;
    return 0;
  }
  status_ = Status::Ok;
  return data_[--size_];
}

bool Stack::isEmpty() const noexcept { return size_ == 0; }

Status Stack::status() const noexcept { return status_; }

std::size_t Stack::size() const noexcept { return size_; }

std::size_t Stack::capacity() const noexcept { return capacity_; }
