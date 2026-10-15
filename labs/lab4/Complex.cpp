#include "Complex.h"
#include <cmath>
#include <stdexcept>

Complex::Complex(double real, double imaginary)
    : _real(real), _imaginary(imaginary) {}

Complex &Complex::operator+=(const Complex &other) {
  _real += other._real;
  _imaginary += other._imaginary;
  return *this;
}

Complex &Complex::operator-=(const Complex &other) {
  _real -= other._real;
  _imaginary -= other._imaginary;
  return *this;
}

Complex &Complex::operator*=(const Complex &other) {
  double newReal = _real * other._real - _imaginary * other._imaginary;
  double newImaginary = _real * other._imaginary + _imaginary * other._real;
  _real = newReal;
  _imaginary = newImaginary;
  return *this;
}

Complex &Complex::operator/=(const Complex &other) {
  double denominator =
      other._real * other._real + other._imaginary * other._imaginary;
  if (denominator == 0) {
    throw std::domain_error("Division by zero");
  }
  double newReal =
      (_real * other._real + _imaginary * other._imaginary) / denominator;
  double newImaginary =
      (_imaginary * other._real - _real * other._imaginary) / denominator;
  _real = newReal;
  _imaginary = newImaginary;
  return *this;
}

double Complex::getReal() const noexcept { return _real; }
double Complex::getImaginary() const noexcept { return _imaginary; }

void Complex::setReal(double real) noexcept { _real = real; }
void Complex::setImaginary(double imaginary) noexcept {
  _imaginary = imaginary;
}

double Complex::getAmplitude() const noexcept {
  return std::sqrt(std::pow(getReal(), 2) + std::pow(getImaginary(), 2));
}
double Complex::getPhase() const noexcept {
  return std::atan2(getImaginary(), getReal());
}

Complex operator+(Complex lhs, const Complex &rhs) { return lhs += rhs; }
Complex operator-(Complex lhs, const Complex &rhs) { return lhs -= rhs; }
Complex operator*(Complex lhs, const Complex &rhs) { return lhs *= rhs; }
Complex operator/(Complex lhs, const Complex &rhs) { return lhs /= rhs; }

bool operator==(const Complex &lhs, const Complex &rhs) {
  return lhs.getReal() == rhs.getReal() &&
         lhs.getImaginary() == rhs.getImaginary();
}
bool operator!=(const Complex &lhs, const Complex &rhs) {
  return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Complex &c) {
  os << c.getReal();
  double imaginary = c.getImaginary();
  if (imaginary != 0) {
    os << (imaginary < 0 ? " - " : " + ") << std::abs(imaginary) << 'i';
  }
  return os;
}
