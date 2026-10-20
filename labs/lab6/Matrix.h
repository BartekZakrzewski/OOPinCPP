#pragma once

class Matrix {
public:
  Matrix(int n, int m);
  Matrix(const Matrix &other);
  Matrix &operator=(const Matrix &other);
  ~Matrix();

  int operator()(int row, int col) const;
  // TODO non-const () operator
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);

  friend bool operator==(const Matrix &lhs, const Matrix &rhs);

private:
  int **_matrix;
  int _n, _m;

  void freeMatrix();

  struct MatrixData {
    int **data;
    int n, m;
    int refCount;

    MatrixData(int n, int m);
    MatrixData(const MatrixData &other);
    ~MatrixData();
    MatrixData &operator=(const MatrixData &other);

  private:
    void allocate();
  };
  MatrixData *_data;

  void detach();
};

Matrix operator+(Matrix lhs, const Matrix &rhs);
Matrix operator-(Matrix lhs, const Matrix &rhs);
Matrix operator*(Matrix lhs, const Matrix &rhs);
bool operator!=(const Matrix &lhs, const Matrix &rhs);
