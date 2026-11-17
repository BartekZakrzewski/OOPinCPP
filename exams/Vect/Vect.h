#pragma once

#include <cstddef>
class Vect {
public:
  Vect();
  Vect(std::size_t n);
  Vect(const Vect &other);
  ~Vect();
  Vect &operator=(const Vect &other);

  void setElement(size_t i, double x);
  void print();

  std::size_t getSize();
  double getAverage();
  double getMin();
  Vect concatenate(const Vect &other);

private:
  double *vect;
  std::size_t size;
};
