#include "Matrix.h"

Matrix::Matrix(int n, int m) {
  if (n <= 0 || m <= 0) {
    throw InvalidDimensionsException();
  }
  _data = new MatrixData(n, m);
}
Matrix::Matrix(const Matrix &other) : _data(other._data) { _data->refCount++; }
Matrix &Matrix::operator=(const Matrix &other) {
  other._data->refCount++;
  if (--_data->refCount == 0)
    delete _data;
  _data = other._data;
  return *this;
}
Matrix::~Matrix() {
  if (--_data->refCount == 0) {
    delete _data;
  }
}

Matrix &Matrix::operator+=(const Matrix &other) {
  if (_data->n != other._data->n || _data->m != other._data->m) {
    throw SizeMismatchException();
  }
  detach();
  for (int row = 0; row < _data->n; row++) {
    for (int col = 0; col < _data->m; col++) {
      _data->data[row][col] += other._data->data[row][col];
    }
  }
  return *this;
}
Matrix &Matrix::operator-=(const Matrix &other) {
  if (_data->n != other._data->n || _data->m != other._data->m) {
    throw SizeMismatchException();
  }
  detach();
  for (int row = 0; row < _data->n; row++) {
    for (int col = 0; col < _data->m; col++) {
      _data->data[row][col] -= other._data->data[row][col];
    }
  }
  return *this;
}
Matrix &Matrix::operator*=(const Matrix &other) {
  if (_data->m != other._data->n) {
    throw MultiplicationMismatchException();
  }
  MatrixData *res = new MatrixData(_data->n, other._data->m);

  for (int i = 0; i < _data->n; i++) {
    for (int j = 0; j < other._data->m; j++) {
      for (int k = 0; k < _data->m; k++) {
        res->data[i][j] += _data->data[i][k] * other._data->data[k][j];
      }
    }
  }
  if (--_data->refCount == 0)
    delete _data;
  _data = res;
  return *this;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
  if (lhs._data->n != rhs._data->n || lhs._data->m != rhs._data->m)
    return false;
  for (int row = 0; row < lhs._data->n; row++) {
    for (int col = 0; col < lhs._data->m; col++) {
      if (lhs._data->data[row][col] != rhs._data->data[row][col]) {
        return false;
      }
    }
  }
  return true;
}

int Matrix::operator()(int row, int col) const {
  checkIndex(row, col);
  return _data->data[row][col];
}

Matrix::Ref Matrix::operator()(int row, int col) {
  checkIndex(row, col);
  return Ref(*this, row, col);
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

void Matrix::detach() {
  if (_data->refCount > 1) {
    MatrixData *copy = new MatrixData(*_data);
    _data->refCount--;
    _data = copy;
  }
}

void Matrix::checkIndex(int row, int col) const {
  if (row < 0 || row >= _data->n || col < 0 || col >= _data->m) {
    throw IndexOutOfRangeException();
  }
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

std::istream &operator>>(std::istream &in, Matrix &m) {
  int n, k;
  if (!(in >> n >> k)) {
    throw MatrixReadExcpetion();
  }
  Matrix tmp(n, k);
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < k; col++) {
      if (!(in >> tmp._data->data[row][col])) {
        throw MatrixReadExcpetion();
      }
    }
  }
  m = tmp;
  return in;
}

Matrix operator+(Matrix lhs, const Matrix &rhs) { return lhs += rhs; }
Matrix operator-(Matrix lhs, const Matrix &rhs) { return lhs -= rhs; }
Matrix operator*(Matrix lhs, const Matrix &rhs) { return lhs *= rhs; }
bool operator!=(const Matrix &lhs, const Matrix &rhs) { return !(lhs == rhs); }

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
  for (int row = 0; row < m.rows(); row++) {
    for (int col = 0; col < m.cols(); col++) {
      if (col)
        os << ' ';
      os << m(row, col);
    }
    os << '\n';
  }
  return os;
}
