#include "InteriorPoint.h"
#include "Matrix.h"

int main() {
  Matrix C(4, 1); // Вектор целевой функции
  C.set(0, 0, 1);
  C.set(1, 0, -2);
  C.set(2, 0, 3);
  C.set(3, 0, 4);

  Matrix A(3, 4); // Матрица ограничений
  A.set(0, 0, 1);
  A.set(0, 1, 1);
  A.set(0, 2, 0);
  A.set(0, 3, 0);
  A.set(1, 0, 0);
  A.set(1, 1, 1);
  A.set(1, 2, 1);
  A.set(1, 3, 0);
  A.set(2, 0, 0);
  A.set(2, 1, 0);
  A.set(2, 2, 1);
  A.set(2, 3, 1);

  Matrix b(3, 1); // Вектор правой части ограничений
  b.set(0, 0, 4);
  b.set(1, 0, 6);
  b.set(2, 0, 8);

  InteriorPoint ip(0.5, 1e-6);
  ip.readProblem(C, A, b);
  ip.solve();
  ip.printResults();
}