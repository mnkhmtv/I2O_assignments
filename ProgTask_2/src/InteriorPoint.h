//
// Created by emil1 on 10/28/2024.
//

#ifndef INTERIORPOINT_H
#define INTERIORPOINT_H

#include "Matrix.h"
#include <vector>

class InteriorPoint {
public:
  explicit InteriorPoint(double alpha, double epsilon);
  void readProblem(Matrix &startingPoint, Matrix &C, Matrix &A, Matrix &b);
  void solve();
  void printResults();

private:
  Matrix C = Matrix(0, 0);
  Matrix A = Matrix(0, 0);
  Matrix b = Matrix(0, 0);
  Matrix x = Matrix(0, 0);
  Matrix D = Matrix(0, 0);
  Matrix A_tilde = Matrix(0, 0);
  Matrix c_tilde = Matrix(0, 0);
  void initializeStartingPoint(Matrix startingPoint);
  double alpha = 0.5;
  double epsilon = 8;
};

#endif // INTERIORPOINT_H
