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

TEST(InteriorPointTest1, SolveAndPrintResultsTest) {
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
      "Optimal solution: x = [\n0.5 \n1.4 \n0.9 \n]\nZ: 14.3\n";

  InteriorPoint ip(0.5, 1);
  ip.readProblem(startingPoint, C, A, b);
  ip.solve();

  std::string output = captureStdout([&]() { ip.printResults(); });

  EXPECT_EQ(output, expected_output);
}

TEST(InteriorPointTest2, SolveAndPrintResultsTest) {
    Matrix startingPoint(2, 1);
    std::vector<std::vector<double>> startingPointMatrix = {{1}, {1}};
    startingPoint.setMatrix(startingPointMatrix);

    Matrix C(2, 1);
    std::vector<std::vector<double>> CMatrix = {{1}, {1}};
    C.setMatrix(CMatrix);

    Matrix A(2, 2);
    std::vector<std::vector<double>> AMatrix = {{1, 1},
                                                {2, 2}};
    A.setMatrix(AMatrix);

    Matrix b(2, 1);
    std::vector<std::vector<double>> bMatrix = {{2}, {4}};
    b.setMatrix(bMatrix);

    std::string expected_output =
        "Optimal solution: x = [\n1 \n1 \n]\nZ: 2\n";

    InteriorPoint ip(0.5, 1);
    ip.readProblem(startingPoint, C, A, b);
    ip.solve();

    std::string output = captureStdout([&]() { ip.printResults(); });

    EXPECT_EQ(output, expected_output);
}

TEST(InteriorPointTest3, SolveAndPrintResultsTest) {
    Matrix startingPoint(2, 1);
    std::vector<std::vector<double>> startingPointMatrix = {{0}, {3}};
    startingPoint.setMatrix(startingPointMatrix);

    Matrix C(2, 1);
    std::vector<std::vector<double>> CMatrix = {{1}, {1}};
    C.setMatrix(CMatrix);

    Matrix A(2, 2);
    std::vector<std::vector<double>> AMatrix = {{2, 4},
                                                {1, 3}};
    A.setMatrix(AMatrix);

    Matrix b(2, 1);
    std::vector<std::vector<double>> bMatrix = {{16}, {9}};
    b.setMatrix(bMatrix);

    std::string expected_output =
        "Optimal solution: x = [\n0 \n3 \n]\nZ: 3\n";

    InteriorPoint ip(0.5, 1);
    ip.readProblem(startingPoint, C, A, b);
    ip.solve();

    std::string output = captureStdout([&]() { ip.printResults(); });

    EXPECT_EQ(output, expected_output);
}

TEST(InteriorPointTest4, SolveAndPrintResultsTest) {
    Matrix startingPoint(2, 1);
    std::vector<std::vector<double>> startingPointMatrix = {{1}, {1}};
    startingPoint.setMatrix(startingPointMatrix);

    Matrix C(2, 1);
    std::vector<std::vector<double>> CMatrix = {{3}, {2}};
    C.setMatrix(CMatrix);

    Matrix A(3, 2);
    std::vector<std::vector<double>> AMatrix = {{1, 1},
                                                {1, 0},
                                                {0, 1}};
    A.setMatrix(AMatrix);

    Matrix b(3, 1);
    std::vector<std::vector<double>> bMatrix = {{4}, {2}, {3}};
    b.setMatrix(bMatrix);

    std::string expected_output =
        "Optimal solution: x = [\n1 \n1 \n]\nZ: 5\n";

    InteriorPoint ip(0.5, 1);
    ip.readProblem(startingPoint, C, A, b);
    ip.solve();

    std::string output = captureStdout([&]() { ip.printResults(); });

    EXPECT_EQ(output, expected_output);
}

TEST(InteriorPointTest5, SolveAndPrintResultsTest) {
    Matrix startingPoint(3, 1);
    std::vector<std::vector<double>> startingPointMatrix = {{1}, {1}, {1}};
    startingPoint.setMatrix(startingPointMatrix);

    Matrix C(3, 1);
    std::vector<std::vector<double>> CMatrix = {{2}, {3}, {4}};
    C.setMatrix(CMatrix);

    Matrix A(3, 3);
    std::vector<std::vector<double>> AMatrix = {{1, 1, 1},
                                                {2, 4, 2},
                                                {1, 3, 0}};
    A.setMatrix(AMatrix);

    Matrix b(3, 1);
    std::vector<std::vector<double>> bMatrix = {{10}, {20}, {12}};
    b.setMatrix(bMatrix);

    std::string expected_output =
        "Optimal solution: x = [\n0.5 \n1.02174 \n1.64286 \n]\nZ: 10.6366\n";

    InteriorPoint ip(0.5, 1);
    ip.readProblem(startingPoint, C, A, b);
    ip.solve();

    std::string output = captureStdout([&]() { ip.printResults(); });

    EXPECT_EQ(output, expected_output);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
