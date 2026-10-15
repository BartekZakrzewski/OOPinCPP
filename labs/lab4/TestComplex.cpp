#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Complex.h"

bool nearlyEqual(double a, double b) { return std::abs(a - b) < 1e-12; }

std::string toString(const Complex &c) {
  std::ostringstream os;
  os << c;
  return os.str();
}

void test_constructors() {
  Complex zero;
  assert(zero.getReal() == 0 && zero.getImaginary() == 0);

  Complex real(3.5);
  assert(real.getReal() == 3.5 && real.getImaginary() == 0);

  Complex full(1, -2);
  assert(full.getReal() == 1 && full.getImaginary() == -2);
}

void test_getters_setters() {
  Complex c;
  c.setReal(4);
  c.setImaginary(-7);
  assert(c.getReal() == 4);
  assert(c.getImaginary() == -7);
}

void test_arithmetic() {
  Complex a(1, 2), b(3, 4);

  assert(a + b == Complex(4, 6));
  assert(a - b == Complex(-2, -2));
  assert(a * b == Complex(-5, 10));
  assert(Complex(-5, 10) / b == a);

  assert(a == Complex(1, 2));
  assert(b == Complex(3, 4));
}

void test_compound_assignment() {
  Complex a(1, 2);
  a += Complex(3, 4);
  assert(a == Complex(4, 6));
  a -= Complex(1, 1);
  assert(a == Complex(3, 5));
  a *= Complex(0, 1);
  assert(a == Complex(-5, 3));
  a /= Complex(0, 1);
  assert(a == Complex(3, 5));

  Complex b(1, 1);
  assert(&(b += Complex(1)) == &b);
  assert(&(b *= Complex(2)) == &b);
}

void test_chaining() {
  Complex a(1, 1), b(2, 2), c(3, 3);
  a += b += c;
  assert(b == Complex(5, 5));
  assert(a == Complex(6, 6));
  assert(c == Complex(3, 3));

  a = Complex(1, 1);
  b = Complex(2, 2);
  (a += b) += c;
  assert(a == Complex(6, 6));
  assert(b == Complex(2, 2));

  a = Complex(1, 1);
  b = Complex(0, 1);
  c = Complex(2);
  a *= b *= c;
  assert(b == Complex(0, 2));
  assert(a == Complex(-2, 2));

  a = Complex(1, 1);
  b = Complex(0, 1);
  (a *= b) *= c;
  assert(a == Complex(-2, 2));
  assert(b == Complex(0, 1));
}

void test_self_operations() {
  Complex a(1, 2);
  a *= a;
  assert(a == Complex(-3, 4));

  a /= a;
  assert(a == Complex(1));

  a -= a;
  assert(a == Complex(0));

  a = Complex(2, 3);
  a += a;
  assert(a == Complex(4, 6));
}

void test_mixed_with_double() {
  Complex a(1, 2), b(3, 4), c(3.5);

  assert(a + 7 == Complex(8, 2));
  assert(7 + a == Complex(8, 2));
  assert(a - 7 == Complex(-6, 2));
  assert(7 - a == Complex(6, -2));
  assert(b * 5 == Complex(15, 20));
  assert(5 * b == Complex(15, 20));
  assert(b / 2 == Complex(1.5, 2));

  assert(c == 3.5);
  assert(3.5 == c);
  assert(c != 3);
  assert(3 != c);
  assert(a != 1);
}

void test_const_objects() {
  const Complex a(1, 2);
  const Complex b(3, 4);

  assert(a.getReal() == 1 && a.getImaginary() == 2);
  assert(a + b == Complex(4, 6));
  assert(a - b == Complex(-2, -2));
  assert(a * b == Complex(-5, 10));
  assert((a * b) / b == a);
  assert(7 + a == Complex(8, 2));
  assert(a == a);
  assert(a != b);
  assert(b.getAmplitude() == 5);
  assert(toString(a) == "1 + 2i");

  Complex c(0);
  c += a;
  assert(c == a);
}

void test_comparison() {
  assert(Complex(1, 2) == Complex(1, 2));
  assert(!(Complex(1, 2) == Complex(1, 3)));
  assert(!(Complex(1, 2) == Complex(2, 2)));
  assert(Complex(1, 2) != Complex(2, 1));
  assert(!(Complex(1, 2) != Complex(1, 2)));
}

void test_division_by_zero() {
  Complex a(1, 1);
  bool thrown = false;
  try {
    a /= Complex(0);
  } catch (const std::domain_error &) {
    thrown = true;
  }
  assert(thrown);
  assert(a == Complex(1, 1));

  thrown = false;
  try {
    Complex result = a / 0;
    (void)result;
  } catch (const std::domain_error &) {
    thrown = true;
  }
  assert(thrown);
}

void test_amplitude_phase() {
  const double pi = std::acos(-1.0);

  assert(Complex(3, 4).getAmplitude() == 5);
  assert(Complex(-3, -4).getAmplitude() == 5);
  assert(Complex(0).getAmplitude() == 0);

  assert(nearlyEqual(Complex(1).getPhase(), 0));
  assert(nearlyEqual(Complex(0, 1).getPhase(), pi / 2));
  assert(nearlyEqual(Complex(-1).getPhase(), pi));
  assert(nearlyEqual(Complex(0, -1).getPhase(), -pi / 2));
  assert(nearlyEqual(Complex(1, 1).getPhase(), pi / 4));
}

void test_stream_insertion() {
  assert(toString(Complex(3, 4)) == "3 + 4i");
  assert(toString(Complex(3, -4)) == "3 - 4i");
  assert(toString(Complex(3)) == "3");
  assert(toString(Complex(0, 1)) == "0 + 1i");
  assert(toString(Complex(-1.5, 2.5)) == "-1.5 + 2.5i");

  std::ostringstream os;
  os << Complex(1, 2) << " and " << Complex(3);
  assert(os.str() == "1 + 2i and 3");
}

int main() {
  test_constructors();
  test_getters_setters();
  test_arithmetic();
  test_compound_assignment();
  test_chaining();
  test_self_operations();
  test_mixed_with_double();
  test_const_objects();
  test_comparison();
  test_division_by_zero();
  test_amplitude_phase();
  test_stream_insertion();

  const Complex example(1, -2);
  std::cout << "Example output: " << example << std::endl;
  std::printf("All tests passed.\n");
  return 0;
}
