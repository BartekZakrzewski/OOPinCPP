#include "Matrix.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void testConstruction();
void testFileInput(Matrix &a, Matrix &b);
void testElementAccess(const Matrix &a);
void testReferenceCounting(const Matrix &a);
void testAddition(const Matrix &a);
void testSubtraction(const Matrix &a);
void testMultiplication(const Matrix &a, const Matrix &b);
void testCompoundAssignment(const Matrix &a, const Matrix &b);
void testComparison(const Matrix &a, const Matrix &b);
void testSelfOperations(const Matrix &a);
void testPassByValue(Matrix m, const Matrix &original);
void testExceptions(const Matrix &a, const Matrix &b);

int main() {
  cout << boolalpha;

  testConstruction();

  Matrix a(1, 1), b(1, 1);
  testFileInput(a, b);

  testElementAccess(a);
  testReferenceCounting(a);
  testAddition(a);
  testSubtraction(a);
  testMultiplication(a, b);
  testCompoundAssignment(a, b);
  testComparison(a, b);
  testSelfOperations(a);

  cout << "\n======= Pass by value =======" << endl;
  cout << "refCount of a before call: " << a.refCount() << endl;
  testPassByValue(a, a);
  cout << "refCount of a after call: " << a.refCount() << endl;

  testExceptions(a, b);
}

void testConstruction() {
  cout << "======= Construction =======" << endl;

  Matrix m(2, 3);
  cout << "New 2x3 matrix (zero initialized):\n" << m;
  cout << "rows: " << m.rows() << ", cols: " << m.cols() << endl;
  cout << "refCount: " << m.refCount() << endl;

  Matrix single(1, 1);
  single(0, 0) = 42;
  cout << "1x1 matrix:\n" << single;
}

void testFileInput(Matrix &a, Matrix &b) {
  cout << "\n======= Reading from file =======" << endl;

  ifstream file("matrix.txt");
  if (!file) {
    cout << "Cannot open matrix.txt" << endl;
    return;
  }
  file >> a >> b;
  cout << "Matrix a (" << a.rows() << "x" << a.cols() << "):\n" << a;
  cout << "Matrix b (" << b.rows() << "x" << b.cols() << "):\n" << b;
  cout << "refCount of a: " << a.refCount() << endl;
}

void testElementAccess(const Matrix &a) {
  cout << "\n======= Element access =======" << endl;

  cout << "a(0, 0) = " << a(0, 0) << ", a(1, 2) = " << a(1, 2) << endl;

  Matrix m = a;
  int sum = 0;
  for (int row = 0; row < m.rows(); row++) {
    for (int col = 0; col < m.cols(); col++) {
      sum += m(row, col);
    }
  }
  cout << "Sum of elements: " << sum << endl;
  cout << "Data still shared after reads (refCount 2): " << m.refCount()
       << endl;

  m(0, 0) = 100;
  cout << "After m(0, 0) = 100, m:\n" << m;
  cout << "a unchanged:\n" << a;
  cout << "refCount of m: " << m.refCount() << ", of a: " << a.refCount()
       << endl;

  m(1, 1) = m(0, 0);
  cout << "After m(1, 1) = m(0, 0), m(1, 1) = " << m(1, 1) << endl;

  Matrix n = a;
  n(0, 1) = m(1, 2);
  cout << "After n(0, 1) = m(1, 2) (n shared with a), n:\n" << n;
  cout << "a unchanged: " << (a(0, 1) == 2) << endl;

  m(0, 1) = m(0, 2) = -1;
  cout << "After m(0, 1) = m(0, 2) = -1, m:\n" << m;
}

void testReferenceCounting(const Matrix &a) {
  cout << "\n======= Reference counting =======" << endl;

  cout << "refCount of a: " << a.refCount() << endl;
  {
    Matrix c1(a);
    Matrix c2 = a;
    cout << "After two copies, refCount: " << a.refCount() << endl;

    Matrix c3(5, 5);
    c3 = a;
    cout << "After assigning a to 5x5 matrix, refCount: " << a.refCount()
         << endl;

    Matrix &self = c3;
    c3 = self;
    cout << "After self assignment, refCount: " << a.refCount() << endl;

    c1(0, 0) = 0;
    cout << "After writing to c1, refCount of a: " << a.refCount()
         << ", of c1: " << c1.refCount() << endl;

    c2 = c1;
    cout << "After c2 = c1, refCount of a: " << a.refCount()
         << ", of c1: " << c1.refCount() << endl;
  }
  cout << "After copies go out of scope, refCount: " << a.refCount() << endl;

  // Chained assignment
  Matrix x(1, 1), y(2, 2), z(3, 3);
  x = y = z = a;
  cout << "After x = y = z = a, refCount: " << a.refCount() << endl;
  x = Matrix(1, 1);
  y = x;
  cout << "After x and y reassigned, refCount of a: " << a.refCount()
       << ", of x: " << x.refCount() << endl;
}

void testAddition(const Matrix &a) {
  cout << "\n======= Addition =======" << endl;

  Matrix sum = a + a;
  cout << "a + a:\n" << sum;
  cout << "a unchanged, refCount: " << a.refCount() << endl;
  cout << "refCount of result: " << sum.refCount() << endl;
}

void testSubtraction(const Matrix &a) {
  cout << "\n======= Subtraction =======" << endl;

  cout << "a - a:\n" << a - a;
  cout << "(a + a) - a == a: " << ((a + a) - a == a) << endl;
}

void testMultiplication(const Matrix &a, const Matrix &b) {
  cout << "\n======= Multiplication =======" << endl;

  // 2x3 * 3x2 = 2x2, 3x2 * 2x3 = 3x3
  cout << "a * b:\n" << a * b;
  cout << "b * a:\n" << b * a;

  Matrix identity(3, 3);
  for (int i = 0; i < 3; i++) {
    identity(i, i) = 1;
  }
  cout << "a * I == a: " << (a * identity == a) << endl;
  cout << "a * b == b * a: " << (a * b == b * a) << endl;
}

void testCompoundAssignment(const Matrix &a, const Matrix &b) {
  cout << "\n======= Compound assignment =======" << endl;

  Matrix m = a;
  m += a;
  cout << "m = a; m += a:\n" << m;
  cout << "Equals a + a: " << (m == a + a)
       << ", a unchanged: " << (a(0, 0) == 1) << endl;

  m = a;
  m -= a;
  cout << "m = a; m -= a:\n" << m;

  m = a;
  m *= b;
  cout << "m = a; m *= b:\n" << m;
  cout << "Equals a * b: " << (m == a * b)
       << ", a unchanged: " << (a.rows() == 2 && a.cols() == 3) << endl;

  Matrix x = a, y = a;
  (x += a) += a;
  cout << "(x += a) += a equals 3a: " << (x == a + a + a) << endl;
  x = a;
  x += y += a;
  cout << "x += y += a equals 3a: " << (x == a + a + a)
       << ", y equals 2a: " << (y == a + a) << endl;
}

void testComparison(const Matrix &a, const Matrix &b) {
  cout << "\n======= Comparison =======" << endl;

  Matrix copy = a;
  cout << "a == copy of a: " << (a == copy) << endl;
  cout << "a != copy of a: " << (a != copy) << endl;
  cout << "a == b (different sizes): " << (a == b) << endl;
  cout << "a != b (different sizes): " << (a != b) << endl;

  Matrix same(2, 3);
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 3; col++) {
      same(row, col) = a(row, col);
    }
  }
  cout << "a == independent matrix with same values: " << (a == same) << endl;
  same(1, 2) = 0;
  cout << "a == same after changing one element: " << (a == same) << endl;
  cout << "a + a != a: " << (a + a != a) << endl;
}

void testSelfOperations(const Matrix &a) {
  cout << "\n======= Self operations =======" << endl;

  Matrix m = a;
  m += m;
  cout << "m = a; m += m equals a + a: " << (m == a + a) << endl;

  m = a;
  m -= m;
  cout << "m = a; m -= m equals zero: " << (m == Matrix(2, 3)) << endl;

  Matrix sq(2, 2);
  sq(0, 0) = 1;
  sq(0, 1) = 2;
  sq(1, 0) = 3;
  sq(1, 1) = 4;
  Matrix shared = sq;
  sq *= sq;
  cout << "sq *= sq:\n" << sq;
  cout << "Shared copy unchanged:\n" << shared;
}

void testPassByValue(Matrix m, const Matrix &original) {
  cout << "refCount inside function: " << m.refCount() << endl;
  m(0, 0) = -100;
  cout << "Modified copy (0, 0): " << m(0, 0)
       << ", original (0, 0): " << original(0, 0) << endl;
}

void testExceptions(const Matrix &a, const Matrix &b) {
  cout << "\n======= Exceptions =======" << endl;

  try {
    Matrix m(0, 3);
    cout << "No exception for 0x3 matrix" << endl;
  } catch (const InvalidDimensionsException &e) {
    cout << "Matrix(0, 3): " << e.what() << endl;
  }

  try {
    Matrix m(3, -1);
    cout << "No exception for 3x-1 matrix" << endl;
  } catch (const InvalidDimensionsException &e) {
    cout << "Matrix(3, -1): " << e.what() << endl;
  }

  try {
    cout << a(2, 0) << endl;
  } catch (const IndexOutOfRangeException &e) {
    cout << "const a(2, 0): " << e.what() << endl;
  }

  try {
    Matrix m = a;
    m(0, -1) = 5;
  } catch (const IndexOutOfRangeException &e) {
    cout << "non-const m(0, -1) = 5: " << e.what() << endl;
  }

  try {
    Matrix m = a;
    m(0, 3) = 5;
  } catch (const IndexOutOfRangeException &e) {
    cout << "non-const m(0, 3) = 5: " << e.what() << endl;
  }

  try {
    cout << a + b;
  } catch (const SizeMismatchException &e) {
    cout << "a + b: " << e.what() << endl;
  }

  try {
    cout << a - b;
  } catch (const SizeMismatchException &e) {
    cout << "a - b: " << e.what() << endl;
  }

  Matrix m = a;
  try {
    m += b;
  } catch (const SizeMismatchException &e) {
    cout << "m += b: " << e.what() << endl;
  }
  cout << "m unchanged after failed +=: " << (m == a)
       << ", still shared: " << (m.refCount() > 1) << endl;

  try {
    cout << a * a;
  } catch (const MultiplicationMismatchException &e) {
    cout << "a * a (2x3 * 2x3): " << e.what() << endl;
  }

  try {
    m *= a;
  } catch (const MultiplicationMismatchException &e) {
    cout << "m *= a: " << e.what() << endl;
  }
  cout << "m unchanged after failed *=: " << (m == a) << endl;

  try {
    istringstream in("2 2\n1 2\n3");
    in >> m;
  } catch (const MatrixReadException &e) {
    cout << "Reading truncated data: " << e.what() << endl;
  }
  cout << "m unchanged after failed read: " << (m == a) << endl;

  try {
    istringstream in("2 2\n1 x 3 4");
    in >> m;
  } catch (const MatrixReadException &e) {
    cout << "Reading non-numeric data: " << e.what() << endl;
  }

  try {
    istringstream in("-2 2\n1 2");
    in >> m;
  } catch (const InvalidDimensionsException &e) {
    cout << "Reading negative dimensions: " << e.what() << endl;
  }

  try {
    istringstream in("");
    in >> m;
  } catch (const MatrixException &e) {
    cout << "Reading empty stream: " << e.what() << endl;
  }

  try {
    cout << b(5, 5);
  } catch (const MatrixException &e) {
    cout << "Caught via MatrixException base: " << e.what() << endl;
  }
  try {
    cout << b(5, 5);
  } catch (const std::runtime_error &e) {
    cout << "Caught via std::runtime_error: " << e.what() << endl;
  }
}
