#include "InteriorPoint.h"
#include <cmath>
#include <iostream>

InteriorPoint::InteriorPoint(double alpha, double epsilon)
    : alpha(alpha), epsilon(epsilon) {}

void InteriorPoint::readProblem(Matrix &startingPoint, Matrix &C, Matrix &A,
                                Matrix &b) {
  this->C = C;
  this->A = A;
  this->b = b;
  initializeStartingPoint(startingPoint);
}

void InteriorPoint::initializeStartingPoint(Matrix startingPoint) {
  int n = C.getRows();
  x = Matrix(n, 1);
  for (int i = 0; i < n; ++i) {
    double current = startingPoint.get(i, 0);
    x.set(i, 0, current);
  }
}

void InteriorPoint::solve() {
  Matrix x_prev = x;
  while (true) {
    int n = x.getRows();
    D = Matrix(n, n);
    for (int i = 0; i < n; ++i) {
      D.set(i, i, x.get(i, 0));
    }

    // Calculate A_tilde = A * D
    A_tilde = A * D;

    // Calculate c_tilde = D * C
    c_tilde = D * C;

    Matrix I = Matrix(A_tilde.getCols());
    Matrix ones = Matrix(A_tilde.getCols(), 1);
    for (int i = 0; i < ones.getRows(); i++) {
      ones.set(i, 0, 1);
    }

    Matrix A_T = A_tilde.transpose();
    Matrix AA_T = A_tilde * A_T;  // A * A transpose

    if (AA_T.determinant(AA_T, AA_T.getRows()) == 0) {
      std::cerr << "The method is not applicable!" << std::endl;
      return;
    }

    Matrix AA_TInv =
        AA_T.inverseMatrix(AA_T, AA_T.getRows());  // A * A transpose) ^ -1

    if (AA_TInv.getRows() == 0 || AA_TInv.getCols() == 0) {
      std::cerr << "The method is not applicable!" << std::endl;
      return;
    }

    Matrix A_TAA_TInv = A_T * AA_TInv;  // A transpose * (A * A transpose) ^ -1
    Matrix A_TAA_TInvA =
        A_TAA_TInv * A_tilde;  // A transpose * (A * A transpose) ^ -1 * A
    Matrix P = I - A_TAA_TInvA;  // I - A transpose * (A * A transpose) ^ -1 * A

    Matrix Cp = P * c_tilde;

    double v = 0;
    for (int i = 0; i < Cp.getRows(); i++) {
      double current = Cp.get(i, 0);
      if (current < 0 && std::abs(current) > v) {
        v = std::abs(current);
      }
    }

    if (v == 0) {
      std::cerr << "The problem does not have solution!" << std::endl;
      return;
    }

    double alphav = alpha / v;
    for (int i = 0; i < ones.getRows(); i++) {
      double current = Cp.get(i, 0);
      Cp.set(i, 0, current * alphav);
    }

    Matrix x_tilda = ones + Cp;
    x = D * x_tilda;

    double norm_diff = 0.0;
    for (int i = 0; i < x.getRows(); i++) {
      double diff = x.get(i, 0) - x_prev.get(i, 0);
      norm_diff += diff * diff;
    }
    norm_diff = std::sqrt(norm_diff);

    if (norm_diff < epsilon) {
      break;
    }

    x_prev = x;
  }
}

void InteriorPoint::printResults() {
  std::cout << "Optimal solution: x = [" << std::endl;
  std::cout << x;
  std::cout << "]" << std::endl;

  double z = 0;
  for (int i = 0; i < x.getRows(); i++) {
    z += x.get(i, 0) * C.get(i, 0);
  }

  std::cout << "Z: " << z << std::endl;
}
