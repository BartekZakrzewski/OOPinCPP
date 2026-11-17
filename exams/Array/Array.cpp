#include "Array.h"
#include <algorithm>
#include <iostream>
#include <ostream>

Array::Array() : size(0) { array = nullptr; }
Array::Array(const Array &other) {
  size = other.size;
  array = new double[size]{};
  std::copy(other.array, other.array + other.size, array);
}
Array::Array(std::size_t n) : size(n) { array = new double[n]{}; }
Array::~Array() { delete[] array; }

double Array::operator[](std::size_t i) const { return array[i]; }
Array &Array::operator=(const Array &other) {
  double *new_array = new double[other.size]{};
  std::copy(other.array, other.array + other.size, new_array);
  delete[] array;
  size = other.size;
  array = new_array;
  return *this;
}

void Array::setElement(size_t i, double x) { array[i] = x; }

void Array::fill(double x) {
  for (std::size_t i = 0; i < size; i++) {
    array[i] = x;
  }
}

void Array::add(double x) {
  double *new_array = new double[size + 1]{};
  std::copy(array, array + size, new_array);
  new_array[size++] = x;
  delete[] array;
  array = new_array;
}

std::size_t Array::getSize() const { return size; }

void Array::swap(Array &other) {
  std::size_t tmp_size = size;
  size = other.size;
  other.size = tmp_size;

  double *tmp_array = array;
  array = other.array;
  other.array = tmp_array;
}

void Array::append(const Array &other) {
  size_t new_size = size + other.size;
  double *new_array = new double[new_size]{};
  for (size_t i = 0; i < size; i++) {
    new_array[i] = array[i];
  }
  for (size_t i = size; i < new_size; i++) {
    new_array[i] = other.array[i - size];
  }
  size = new_size;
  delete[] array;
  array = new_array;
}

std::ostream &operator<<(std::ostream &os, const Array &a) {
  os << '[';
  for (std::size_t i = 0; i < a.getSize(); i++) {
    os << a[i] << (i == (a.getSize() - 1) ? "]" : ", ");
  }
  return os;
}
