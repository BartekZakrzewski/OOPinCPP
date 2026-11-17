#include "Vect.h"
#include <algorithm>
#include <cstddef>
#include <iostream>

Vect::Vect() : size(0) { vect = nullptr; }
Vect::Vect(std::size_t n) : size(n) { vect = new double[size]{}; }
Vect::Vect(const Vect &other) {
  size = other.size;
  vect = new double[size]{};
  std::copy(other.vect, other.vect + other.size, vect);
}
Vect::~Vect() { delete[] vect; }
Vect &Vect::operator=(const Vect &other) {
  size = other.size;
  vect = new double[size]{};
  std::copy(other.vect, other.vect + other.size, vect);
  return *this;
}

void Vect::setElement(size_t i, double x) { vect[i] = x; }
void Vect::print() {
  std::cout << "[";
  for (std::size_t i = 0; i < size; i++) {
    std::cout << vect[i] << (i < size - 1 ? ", " : "");
  }
  std::cout << "]";
}

std::size_t Vect::getSize() { return size; }
double Vect::getAverage() {
  if (size == 0)
    return 0.0;
  double avg = 0.0;
  for (std::size_t i = 0; i < size; i++) {
    avg += vect[i];
  }
  return avg / size;
}

double Vect::getMin() {
  if (size == 0)
    return 0.0;
  double min = vect[0];
  for (std::size_t i = 1; i < size; i++) {
    if (vect[i] < min)
      min = vect[i];
  }
  return min;
}

Vect Vect::concatenate(const Vect &other) {
  Vect tmp_vect(size + other.size);
  for (std::size_t i = 0; i < size; i++)
    tmp_vect.vect[i] = vect[i];
  for (std::size_t i = 0; i < other.size; i++)
    tmp_vect.vect[i + size] = other.vect[i];
  return tmp_vect;
}
