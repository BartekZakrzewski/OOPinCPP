#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

// clang-format off
class MatrixException : public std::runtime_error {
public: explicit MatrixException(const std::string &msg) : std::runtime_error(msg) {}
};

class InvalidDimensionsException : public MatrixException {
public: InvalidDimensionsException() : MatrixException("Matrix dimensions must be positive") {}
};
class IndexOutOfRangeException : public MatrixException {
public: IndexOutOfRangeException() : MatrixException("Matrix index out of range") {}
};
class SizeMismatchException : public MatrixException {
public: SizeMismatchException() : MatrixException("Matrices must have the same size") {}
};
class MultiplicationMismatchException : public MatrixException {
public: MultiplicationMismatchException() : MatrixException("Left columns must equal right rows") {}
};
class MatrixReadException : public MatrixException {
public: MatrixReadException() : MatrixException("Invalid matrix data in stream") {} 
};
// clang-format on

class Matrix {
public:
  Matrix(int n, int m);
  Matrix(const Matrix &other);
  Matrix &operator=(const Matrix &other);
  ~Matrix();

  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);

  friend bool operator==(const Matrix &lhs, const Matrix &rhs);

  class Ref {
    friend class Matrix;
    Matrix &_m;
    int _row, _col;
    Ref(Matrix &m, int row, int col) : _m(m), _row(row), _col(col) {}

  public:
    operator int() const { return _m._data->data[_row][_col]; }
    Ref &operator=(int value) {
      _m.detach();
      _m._data->data[_row][_col] = value;
      return *this;
    }
    Ref &operator=(const Ref &other) { return *this = static_cast<int>(other); }
  };

  int operator()(int row, int col) const;
  Ref operator()(int row, int col);

  int rows() const { return _data->n; }
  int cols() const { return _data->m; }
  int refCount() const { return _data->refCount; }

  friend std::istream &operator>>(std::istream &in, Matrix &m);

private:
  struct MatrixData {
    int **data;
    int n, m;
    int refCount;

    MatrixData(int n, int m);
    MatrixData(const MatrixData &other);
    ~MatrixData();
    MatrixData &operator=(const MatrixData &other) = delete;

  private:
    void allocate();
  };
  MatrixData *_data;

  void checkIndex(int row, int col) const;
  void detach();
};

Matrix operator+(Matrix lhs, const Matrix &rhs);
Matrix operator-(Matrix lhs, const Matrix &rhs);
Matrix operator*(Matrix lhs, const Matrix &rhs);
bool operator!=(const Matrix &lhs, const Matrix &rhs);

std::ostream &operator<<(std::ostream &os, const Matrix &m);
