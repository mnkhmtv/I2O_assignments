#include <iostream>
#include <vector>

#include "InteriorPoint.h"
#include "Matrix.h"
#include "Simplex/Simplex.h"

int main() {
  Matrix startingPoint(3, 1);
  std::vector<std::vector<double>> startingPointMatrix = {{1}, {1}, {1}};
  startingPoint.setMatrix(startingPointMatrix);

  Matrix C(3, 1);
  std::vector<std::vector<double>> CMatrix = {{2}, {5}, {7}};
  C.setMatrix(CMatrix);

  Matrix A(1, 3);
  std::vector<std::vector<double>> AMatrix = {{1, 2, 3}};
  A.setMatrix(AMatrix);

  Matrix b(1, 1);
  std::vector<std::vector<double>> bMatrix = {{6}};
  b.setMatrix(bMatrix);

  std::cout << "Interior-Point method with α = 0.5:" << std::endl;
  InteriorPoint ip(0.5, 1e-6);
  ip.readProblem(startingPoint, C, A, b);
  ip.solve();
  ip.printResults();

  std::cout << std::endl;

  std::cout << "Interior-Point method with α = 0.9:" << std::endl;
  InteriorPoint ip1(0.9, 1e-6);
  ip1.readProblem(startingPoint, C, A, b);
  ip1.solve();
  ip1.printResults();

  std::cout << std::endl;

  std::vector<double> C_simplex = {2, 5, 7};
  std::vector<std::vector<double>> A_simplex = {{1, 2, 3}};
  std::vector<double> b_simplex = {6};
  double epsilon = 2;

  std::cout << "Simplex method:" << std::endl;
  simplex(C_simplex, A_simplex, b_simplex, epsilon);

  return 0;
}
