// Class Poly is defined in file Poly.h
#include "Poly.h"

#include <iostream>

using namespace std;

void displayNonConst(Poly &p);
void displayConst(const Poly &p);
void test(const Poly &p1, const Poly &p2);
void testAddition(const Poly &p1, const Poly &p2);
void testSubtraction(const Poly &p1, const Poly &p2);
void testMultiplication(const Poly &p1, const Poly &p2);
void testValue(const Poly &p1, const Poly &p2);
void testComparison(const Poly &p1, const Poly &p2);
void testUnaryMinus(const Poly &p1);
void testCompoundAssignment(const Poly &p1, const Poly &p2);
void testCoefficients(const Poly &p1, const Poly &p2);
void testSelfOperations(const Poly &p1);
void testZero(const Poly &p1);

int main() {
  // Declare object representing polynomial p1
  Poly p1;

  // Specify coefficients of p1 = -2.3x^3 + 5x^2 - 4.5
  p1[3] = -2.3;
  p1[2] = 5;
  p1[0] = -4.5;

  cout << "======= Polynomial p1 =======" << endl;
  cout << p1 << endl;

  // Declare object representing polynomial p2 = 2.6
  Poly p2 = 2.6;

  // Specify additional coefficient of p2 = x^4 - 7x^2 + 3x + 2.6
  p2[1] = 3;
  p2[2] = -7;
  p2[4] = 1;

  cout << "\n======= Polynomial p2 =======" << endl;
  displayNonConst(p2);
  displayConst(p2);

  test(p1, p2);
}

// Code is duplicated in the following two functions. This could be refactored
// using function template, but the duplication is left, because function
// template may not have been explained on the lecture yet and the code could be
// unclear.

void displayNonConst(Poly &p) {
  cout << p << endl;

  // Display coefficients. If coefficient does not exist, display 0.
  for (int i = 5; i >= 0; --i) {
    cout << "\tCoefficient " << i << ": " << p[i] << endl;
  }
}

void displayConst(const Poly &p) {
  cout << p << endl;

  // Display coefficients. If coefficient does not exist, display 0.
  for (int i = 5; i >= 0; --i) {
    cout << "\tCoefficient " << i << ": " << p[i] << endl;
  }
}

void test(const Poly &p1, const Poly &p2) {
  testAddition(p1, p2);
  testSubtraction(p1, p2);
  testMultiplication(p1, p2);
  testValue(p1, p2);

  cout << boolalpha;
  testComparison(p1, p2);
  testUnaryMinus(p1);
  testCompoundAssignment(p1, p2);
  testCoefficients(p1, p2);
  testSelfOperations(p1);
  testZero(p1);
}

void testAddition(const Poly &p1, const Poly &p2) {
  cout << "\n======= Addition =======" << endl;

  Poly p = p1 + p2;
  cout << "Sum of polynomials p1 and p2: " << p << endl;

  p = p1 + 2.4;
  cout << "Sum of polynomial p1 and 2.4: " << p << endl;

  p = 2.4 + p1;
  cout << "Sum of 2.4 and polynomial p1: " << p << endl;
}

void testSubtraction(const Poly &p1, const Poly &p2) {
  cout << "\n======= Subtraction =======" << endl;

  cout << "Difference of polynomials p1 and p2: " << p1 - p2 << endl;

  // The following should display 0 (not 0x^3 + 0x^2 + 0)
  cout << "Difference of polynomials p1 and p1: " << p1 - p1 << endl;

  cout << "Difference of polynomial p1 and 5.3: " << p1 - 5.3 << endl;
  cout << "Difference of 5.3 and polynomial p1: " << 5.3 - p1 << endl;
}

void testMultiplication(const Poly &p1, const Poly &p2) {
  cout << "\n======= Multiplication =======" << endl;

  cout << "Product of polynomials p1 and p2: " << p1 * p2 << endl;
  cout << "6.7 multiplied by polynomial p1: " << 6.7 * p1 << endl;
  cout << "Polynomial p1 multiplied by 6.7: " << p1 * 6.7 << endl;
}

void testValue(const Poly &p1, const Poly &p2) {
  cout << "\n======= Value =======" << endl;

  cout << "Value of polynomial p1 at point  3.9: " << p1(3.9) << endl;
  cout << "Value of polynomial p2 at point -2.8: " << p2(-2.8) << endl;
}

void testComparison(const Poly &p1, const Poly &p2) {
  cout << "\n======= Comparison =======" << endl;

  Poly copy = p1;
  cout << "p1 == copy of p1: " << (p1 == copy) << endl;
  cout << "p1 != copy of p1: " << (p1 != copy) << endl;
  cout << "p1 == p2: " << (p1 == p2) << endl;
  cout << "p1 != p2: " << (p1 != p2) << endl;
  cout << "p1 + p2 == p2 + p1: " << (p1 + p2 == p2 + p1) << endl;
  cout << "p1 * p2 == p2 * p1: " << (p1 * p2 == p2 * p1) << endl;
  cout << "Poly(2.6) == 2.6: " << (Poly(2.6) == 2.6) << endl;
  cout << "p1 - p1 == 0: " << (p1 - p1 == 0) << endl;
}

void testUnaryMinus(const Poly &p1) {
  cout << "\n======= Unary minus =======" << endl;

  cout << "Negation of p1: " << -p1 << endl;
  cout << "-(-p1) == p1: " << (-(-p1) == p1) << endl;
  cout << "p1 + (-p1): " << p1 + (-p1) << endl;
  cout << "Negation of zero polynomial: " << -Poly() << endl;
}

void testCompoundAssignment(const Poly &p1, const Poly &p2) {
  cout << "\n======= Compound assignment =======" << endl;

  Poly p = p1;
  p += p2;
  cout << "p1 += p2: " << p << " (equals p1 + p2: " << (p == p1 + p2) << ")"
       << endl;

  p = p1;
  p -= p2;
  cout << "p1 -= p2: " << p << " (equals p1 - p2: " << (p == p1 - p2) << ")"
       << endl;

  p = p1;
  p *= p2;
  cout << "p1 *= p2: " << p << " (equals p1 * p2: " << (p == p1 * p2) << ")"
       << endl;

  p = p1;
  p += 2.4;
  cout << "p1 += 2.4: " << p << endl;

  p = p1;
  p *= 0;
  cout << "p1 *= 0: " << p << endl;
}

void testCoefficients(const Poly &p1, const Poly &p2) {
  cout << "\n======= Coefficients =======" << endl;

  // Assigning 0 should remove the term
  Poly p = p1;
  p[2] = 0;
  cout << "p1 with coefficient 2 set to 0: " << p << endl;
  p[3] = 0;
  p[0] = 0;
  cout << "p1 with all coefficients set to 0: " << p << endl;
  cout << "Equals zero polynomial: " << (p == Poly()) << endl;

  // Reading missing coefficients through non-const operator[] must not add them
  Poly q = p2;
  double sum = 0;
  for (int i = 10; i >= 0; --i) {
    sum += q[i];
  }
  cout << "Sum of coefficients 0..10 of p2: " << sum << endl;
  cout << "Reading coefficients did not change p2: " << (q == p2) << endl;

  // Assigning coefficient from another polynomial and from the same one
  p = p1;
  p[1] = q[1];
  cout << "p1 with coefficient 1 copied from p2: " << p << endl;
  p[4] = p[1];
  cout << "Coefficient 1 copied to coefficient 4: " << p << endl;
  p[1] = q[3];
  cout << "Coefficient 1 copied from missing coefficient 3 of p2: " << p
       << endl;

  // Modifying a copy must not change the original
  Poly copy = p1;
  copy[3] = 1;
  cout << "Modified copy of p1: " << copy << endl;
  cout << "Original p1: " << p1 << endl;
}

void testSelfOperations(const Poly &p1) {
  cout << "\n======= Self operations =======" << endl;

  Poly p = p1;
  p -= p;
  cout << "p1 -= p1: " << p << endl;

  p = p1;
  p += p;
  cout << "p1 += p1: " << p << " (equals 2 * p1: " << (p == 2 * p1) << ")"
       << endl;

  p = p1;
  p *= p;
  cout << "p1 *= p1: " << p << " (equals p1 * p1: " << (p == p1 * p1) << ")"
       << endl;
}

void testZero(const Poly &p1) {
  cout << "\n======= Zero polynomial =======" << endl;

  Poly zero;
  cout << "Default polynomial: " << zero << endl;
  cout << "Poly(0): " << Poly(0) << endl;
  cout << "Value of zero polynomial at point 3.9: " << zero(3.9) << endl;
  cout << "Value of polynomial p1 at point 0: " << p1(0) << endl;
  cout << "Zero polynomial multiplied by p1: " << zero * p1 << endl;
  cout << "p1 multiplied by 0: " << p1 * 0 << endl;
  cout << "p1 plus zero polynomial equals p1: " << (p1 + zero == p1) << endl;

  Poly r = 0.1;
  r += 0.2;
  r -= 0.3;
  cout << "0.1 + 0.2 - 0.3 as polynomial: " << r << endl;
}
