//
// Created by emil1 on 10/28/2024.
//
#include <iosfwd>
#include <vector>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
  Matrix(int rows, int cols);
  Matrix(int i);                                    // Identity matrix
  Matrix(int rows, int cols, Matrix &A, Matrix &B); // Augmented Matrix
  friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
  friend std::istream &operator>>(std::istream &in, Matrix &m);
  Matrix operator+(Matrix &m);
  Matrix operator-(Matrix &m);
  Matrix operator*(Matrix &m);
  Matrix operator=(Matrix const &m);
  Matrix transpose();
  const std::vector<std::vector<double>> &getMatrix() const;
  int getCols() const;
  int getRows() const;
  double get(int row, int col);
  void set(int row, int col, double value);
  void setMatrix(std::vector<std::vector<double>> matrix);
  Matrix inverseMatrix(Matrix &A, int n);
  double determinant(Matrix &A, int n);
  int gauseElimination(Matrix &A, int n);
  int maxPivot(int col);

private:
  int rows;
  int cols;

protected:
  std::vector<std::vector<double>> matrix;
};

class PermutationMatrix : public Matrix {
public:
  explicit PermutationMatrix(int size);
  void swap(int i, int j);

private:
  int size;
};

class EliminationMatrix : public Matrix {
public:
  explicit EliminationMatrix(int size);
  void eliminate(int i, int j, double multiplier);

private:
  int size;
};

#endif // MATRIX_H
