#pragma once
#include <ostream>

class Complex {
public:
  Complex(double real = 0, double imaginary = 0);

  Complex &operator+=(const Complex &other);
  Complex &operator-=(const Complex &other);
  Complex &operator*=(const Complex &other);
  Complex &operator/=(const Complex &other);

  double getReal() const noexcept;
  double getImaginary() const noexcept;
  void setReal(double real) noexcept;
  void setImaginary(double imaginary) noexcept;

  double getAmplitude() const noexcept;
  double getPhase() const noexcept;

private:
  double _real;
  double _imaginary;
};

Complex operator+(Complex lhs, const Complex &rhs);
Complex operator-(Complex lhs, const Complex &rhs);
Complex operator*(Complex lhs, const Complex &rhs);
Complex operator/(Complex lhs, const Complex &rhs);

bool operator==(const Complex &lhs, const Complex &rhs);
bool operator!=(const Complex &lhs, const Complex &rhs);

std::ostream &operator<<(std::ostream &os, const Complex &c);
