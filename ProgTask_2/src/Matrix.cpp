//
// Created by emil1 on 10/28/2024.
//

#include "Matrix.h"
#include <complex>
#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>

Matrix::Matrix(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
  matrix.resize(rows);
  for (int i = 0; i < rows; i++) {
    matrix[i].resize(cols);
  }
}

Matrix::Matrix(int i) {
  this->rows = i;
  this->cols = i;
  matrix.resize(i);
  for (int j = 0; j < i; j++) {
    matrix[j].resize(i);
    for (int p = 0; p < i; p++) {
      if (j == p) {
        matrix[j][p] = 1;
      } else {
        matrix[j][p] = 0;
      }
    }
  }
}

void Matrix::set(int row, int col, double value) { matrix[row][col] = value; }

double Matrix::get(int row, int col) const { return matrix[row][col]; }

int Matrix::getRows() const { return rows; }

int Matrix::getCols() const { return cols; }

const std::vector<std::vector<double>> &Matrix::getMatrix() const {
  return matrix;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {
      os << m.matrix[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}

std::istream &operator>>(std::istream &in, Matrix &m) {
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {
      in >> m.matrix[i][j];
    }
  }
  return in;
}

Matrix Matrix::operator+(const Matrix &m) const {
    Matrix result(rows, cols);
    if (m.rows != rows || m.cols != cols) {
        throw "Error";
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.set(i, j, matrix[i][j] + m.get(i, j));
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &m) const {
    Matrix result(rows, cols);
    if (m.rows != rows || m.cols != cols) {
        throw "Error";
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.set(i, j, matrix[i][j] - m.get(i, j));
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &m) const {
    Matrix result(rows, m.cols);
    if (m.rows != cols) {
        throw "Error";
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            for (int k = 0; k < cols; k++) {
                result.set(i, j, result.get(i, j) + matrix[i][k] * m.get(k, j));
            }
        }
    }
    return result;
}

Matrix& Matrix::operator=(const Matrix &m) {
    if (this != &m) {
        rows = m.rows;
        cols = m.cols;
        matrix = m.matrix;
    }
    return *this;
}

Matrix Matrix::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      result.set(i, j, matrix[j][i]);
    }
  }
  return result;
}
Matrix Matrix::inverseMatrix(Matrix &A, int n) {
  int permutation = 0;
  int step = 0;
  std::unique_ptr<Matrix> I = std::make_unique<Matrix>(n);

  Matrix B = A;
  // check singularity
  if (determinant(B, n) == 0) {
    throw "Error: matrix A is singular";
  }

  Matrix C1(A.getRows(), A.getCols() + I->getCols(), A, *I);

  for (int i = 0; i < n; i++) {
    int maxIndex = A.maxPivot(i);
    if (maxIndex == -1 || i == n - 1) {
      maxIndex = i;
    }

    if (maxIndex != i && i != n - 1) {
      PermutationMatrix P(n);
      P.swap(i, maxIndex);
      A = P * A;
      *I = P * *I;
      Matrix C(A.getRows(), A.getCols() + I->getCols(), A, *I);
      permutation++;
    }

    for (int j = i + 1; j < n; j++) {
      if (A.get(i, i) != 0) {
        double multiplier = A.get(j, i) / A.get(i, i);
        if (multiplier != 0) {
          EliminationMatrix E(n);
          E.eliminate(i, j, multiplier);
          A = E * A;
          *I = E * *I;
          Matrix C(A.getRows(), A.getCols() + I->getCols(), A, *I);
        }
      }
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i - 1; j >= 0; j--) {
      if (A.get(i, i) != 0) {
        double multiplier = A.get(j, i) / A.get(i, i);
        if (multiplier != 0) {
          EliminationMatrix E(n);
          E.eliminate(i, j, multiplier);
          A = E * A;
          *I = E * *I;
          Matrix C(A.getRows(), A.getCols() + I->getCols(), A, *I);
        }
      }
    }
  }

  for (int j = 0; j < n; j++) {
    double multiplier = 1 / A.get(j, j);
    for (int i = 0; i < n; i++) {
      if (multiplier != 0) {
        A.set(j, i, A.get(j, i) * multiplier);
        I->set(j, i, I->get(j, i) * multiplier);
      }
    }
  }
  Matrix C(A.getRows(), A.getCols() + I->getCols(), A, *I);

  return *I;
}

Matrix::Matrix(int rows, int cols, Matrix &A, Matrix &B) : Matrix(rows, cols) {
  for (int i = 0; i < A.getRows(); i++) {
    for (int j = 0; j < A.getCols() + B.getCols(); j++) {
      if (j < A.getCols()) {
        set(i, j, A.get(i, j));
      } else {
        set(i, j, B.get(i, j - A.getCols()));
      }
    }
  }
}
double Matrix::determinant(Matrix &A, int n) {
  int permutations = gauseElimination(A, n);
  double det = 1;
  if (permutations % 2 == 1) {
    det = -1;
  }
  for (int i = 0; i < n; i++) {
    det *= A.get(i, i);
  }
  return det;
}

int Matrix::gauseElimination(Matrix &A, int n) {
  int permutation = 0;
  for (int i = 0; i < n; i++) {
    int maxIndex = A.maxPivot(i);
    if (maxIndex == -1 || i == n - 1) {
      maxIndex = i;
    }

    if (maxIndex != i && i != n - 1) {
      PermutationMatrix P(n);
      P.swap(i, maxIndex);
      A = P * A;
      permutation++;
    }

    for (int j = i + 1; j < n; j++) {
      if (A.get(i, i) != 0) {
        double multiplier = A.get(j, i) / A.get(i, i);
        if (multiplier != 0) {
          EliminationMatrix E(n);
          E.eliminate(i, j, multiplier);
          A = E * A;
        }
      }
    }
  }
  return permutation;
}
int Matrix::maxPivot(int col) {
  double max = 0;
  int maxIndex = col;
  for (int i = col; i < rows; i++) {
    if (std::abs(matrix[i][col]) > max) {
      max = std::abs(matrix[i][col]);
      maxIndex = i;
    }
  }
  if (std::abs(matrix[col][col]) == max) {
    maxIndex = -1;
  }
  return maxIndex;
}

PermutationMatrix::PermutationMatrix(int size)
    : Matrix(size, size), size(size) {
  for (int i = 0; i < size; ++i) {
    set(i, i, 1);
  }
}
void PermutationMatrix::swap(int i, int j) {
  for (int k = 0; k < size; ++k) {
    std::swap(matrix[i][k], matrix[j][k]);
  }
}

void EliminationMatrix::eliminate(int i, int j, double multiplier) {
  for (int k = 0; k < size; ++k) {
    matrix[j][k] -= multiplier * matrix[i][k];
  }
}

EliminationMatrix::EliminationMatrix(int size)
    : Matrix(size, size), size(size) {
  for (int i = 0; i < size; ++i) {
    set(i, i, 1);
  }
}

void Matrix::setMatrix(std::vector<std::vector<double>> matrix) {
  this->matrix = matrix;
}
