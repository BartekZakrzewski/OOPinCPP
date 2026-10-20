#include "Matrix.h"

Matrix::Matrix(int n, int m) : _data(new MatrixData(n, m)) {}
Matrix::Matrix(const Matrix &other) : _data(other._data) { _data->refCount++; }
Matrix &Matrix::operator=(const Matrix &other) {
  other._data->refCount++;
  if (--_data->refCount == 0)
    delete _data;
  _data = other._data;
  return *this;
}
Matrix::~Matrix() {
  if (--_data->refCount == 0)
    delete _data;
}

int Matrix::operator()(int row, int col) const {
  return *(*(_matrix + row) + col);
}
Matrix &Matrix::operator+=(const Matrix &other) {
  // TODO Size check; if (_n != other._n || _m != other._m) return;
  for (int row = 0; row < _n; row++) {
    for (int col = 0; col < _m; col++) {
      _matrix[row][col] += other._matrix[row][col];
    }
  }
  return *this;
}
Matrix &Matrix::operator-=(const Matrix &other) {
  // TODO Size check; if (_n != other._n || _m != other._m) return;
  for (int row = 0; row < _n; row++) {
    for (int col = 0; col < _m; col++) {
      _matrix[row][col] -= other._matrix[row][col];
    }
  }
  return *this;
}
Matrix &Matrix::operator*=(const Matrix &other) {
  // TODO Size check;
  int **res = new int *[_n];
  for (int i = 0; i < _n; i++)
    res[i] = new int[other._m]();
  for (int i = 0; i < _n; i++) {
    for (int j = 0; j < other._m; j++) {
      for (int k = 0; k < _m; k++) {
        res[i][j] += _matrix[i][k] * other._matrix[k][j];
      }
    }
  }
  freeMatrix();
  _matrix = res;
  _m = other._m;
  return *this;
}

void Matrix::freeMatrix() {
  for (int i = 0; i < _n; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

void Matrix::MatrixData::allocate() {
  data = new int *[n];
  int i = 0;
  try {
    for (; i < n; i++) {
      data[i] = new int[m]();
    }
  } catch (...) {
    for (int j = 0; j < i; j++) {
      delete[] data[j];
    }
    delete[] data;
    throw;
  }
}

Matrix::MatrixData::MatrixData(int n, int m) : n(n), m(m), refCount(1) {
  allocate();
}

Matrix::MatrixData::MatrixData(const MatrixData &other)
    : n(other.n), m(other.m), refCount(1) {
  allocate();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      data[i][j] = other.data[i][j];
    }
  }
}

Matrix::MatrixData::~MatrixData() {
  for (int i = 0; i < n; i++) {
    delete[] data[i];
  }
  delete[] data;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
  if (lhs._n != rhs._n || lhs._m != rhs._m)
    return false;
  for (int row = 0; row < lhs._n; row++) {
    for (int col = 0; col < lhs._m; col++) {
      if (lhs._matrix[row][col] != rhs._matrix[row][col]) {
        return false;
      }
    }
  }
  return true;
}

Matrix operator+(Matrix lhs, const Matrix &rhs) { return lhs += rhs; }
Matrix operator-(Matrix lhs, const Matrix &rhs) { return lhs -= rhs; }
Matrix operator*(Matrix lhs, const Matrix &rhs) { return lhs *= rhs; }
bool operator!=(const Matrix &lhs, const Matrix &rhs) { return !(lhs == rhs); }
