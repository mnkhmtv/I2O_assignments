#include "../src/InteriorPoint.h"
#include "../src/Matrix.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

// Helper function to capture stdout
std::string captureStdout(std::function<void()> func) {
  std::ostringstream oss;
  std::streambuf *oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

  func(); // Execute the function

  std::cout.rdbuf(oldCoutBuffer); // Restore the old buffer
  return oss.str();               // Return captured output
}

TEST(InteriorPointTest, SolveAndPrintResultsTest) {
  Matrix startingPoint(3, 1);
  std::vector<std::vector<double>> startingPointMatrix = {{1}, {1}, {1}};
  startingPoint.setMatrix(startingPointMatrix);

  // Create test data for vector C, matrix A, and vector b
  Matrix C(3, 1); // Objective function vector
  std::vector<std::vector<double>> CMatrix = {{2}, {5}, {7}};
  C.setMatrix(CMatrix);

  Matrix A(1, 3); // Constraint matrix
  std::vector<std::vector<double>> AMatrix = {{1, 2, 3}};
  A.setMatrix(AMatrix);

  Matrix b(1, 1); // Right-hand side vector
  std::vector<std::vector<double>> bMatrix = {{6}};
  b.setMatrix(bMatrix);

  // Expected output from printResults
  std::string expected_output = "Optimal solution: \n"
                                "0.78 \n"
                                "3.48 \n"
                                "0.50 \n"
                                "2.23 \n"
                                "Z: 4.26\n";

  // Create an instance of InteriorPoint
  InteriorPoint ip(0.5, 1);
  ip.readProblem(startingPoint, C, A, b);
  ip.solve(); // Execute solve method

  // Capture output of printResults after solve
  std::string output = captureStdout([&]() {
    ip.printResults(); // Print results
  });

  // Verify output matches expected
  EXPECT_EQ(output, expected_output);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
