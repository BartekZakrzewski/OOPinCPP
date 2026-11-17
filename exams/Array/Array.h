#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

class Array {
public:
  Array();
  Array(const Array &other);
  Array(std::size_t n);
  ~Array();

  double operator[](std::size_t i) const;
  Array &operator=(const Array &other);

  void setElement(size_t i, double x);
  void fill(double x);
  void add(double x);
  std::size_t getSize() const;
  void swap(Array &other);
  void append(const Array &other);

private:
  std::size_t size;
  double *array;
};

std::ostream &operator<<(std::ostream &os, const Array &a);
