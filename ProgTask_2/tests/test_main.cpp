#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "../src/InteriorPoint.h"
#include "../src/Matrix.h"


std::string captureStdout(std::function<void()> func) {
  std::ostringstream oss;
  std::streambuf *oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

  func();

  std::cout.rdbuf(oldCoutBuffer);
  return oss.str();
}

TEST(InteriorPointTest, SolveAndPrintResultsTest) {
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

  std::string expected_output =
      "Optimal solution: x = [\n2.14577e-07 \n3 \n2.14577e-07 \n]\nZ: 15\n";

  InteriorPoint ip(0.5, 1e-6);
  ip.readProblem(startingPoint, C, A, b);
  ip.solve();

  std::string output = captureStdout([&]() { ip.printResults(); });

  EXPECT_EQ(output, expected_output);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
