// Simplex.cpp
#include "Simplex.h"

void print_problem(const std::vector<double> &C,
                   const std::vector<std::vector<double>> &A,
                   const std::vector<double> &b) {
  int num_vars = C.size();
  int num_constraints = A.size();

  std::cout << "Optimization problem:" << std::endl;
  std::cout << "max z = ";
  for (int i = 0; i < num_vars; ++i) {
    std::cout << C[i] << " * x" << (i + 1);
    if (i < num_vars - 1)
      std::cout << " + ";
  }
  std::cout << std::endl;

  std::cout << "subject to the constraints:" << std::endl;
  for (int i = 0; i < num_constraints; ++i) {
    for (int j = 0; j < num_vars; ++j) {
      std::cout << A[i][j] << " * x" << (j + 1);
      if (j < num_vars - 1)
        std::cout << " + ";
    }
    std::cout << " <= " << b[i] << std::endl;
  }
  std::cout << std::endl;
}

void simplex(std::vector<double> C, std::vector<std::vector<double>> A,
             std::vector<double> b, double epsilon) {
  int num_vars = C.size();
  int num_constraints = A.size();
  int total_vars = num_vars + num_constraints;
  std::vector<std::vector<double>> table(
      num_constraints + 1, std::vector<double>(total_vars + 1, 0));
  print_problem(C, A, b);
  for (int i = 0; i < num_constraints; ++i) {
    for (int j = 0; j < num_vars; ++j) {
      table[i][j] = A[i][j];
    }
    table[i][num_vars + i] = 1;
    table[i].back() = b[i];
  }

  for (int j = 0; j < num_vars; ++j) {
    table.back()[j] = -C[j];
  }
  while (true) {
    int pivot_col = -1;
    for (int j = 0; j < total_vars; ++j) {
      if (table.back()[j] < -EPS) {
        pivot_col = j;
        break;
      }
    }
    if (pivot_col == -1)
      break;

    int pivot_row = -1;
    double min_ratio = std::numeric_limits<double>::infinity();
    for (int i = 0; i < num_constraints; ++i) {
      if (table[i][pivot_col] > EPS) {
        double ratio = table[i].back() / table[i][pivot_col];
        if (ratio < min_ratio) {
          min_ratio = ratio;
          pivot_row = i;
        }
      }
    }

    if (pivot_row == -1) {
      std::cout << "The problem is unbounded." << std::endl;
      return;
    }

    double pivot_val = table[pivot_row][pivot_col];
    for (double &val : table[pivot_row]) {
      val /= pivot_val;
    }

    for (int i = 0; i <= num_constraints; ++i) {
      if (i != pivot_row) {
        double factor = table[i][pivot_col];
        for (int j = 0; j <= total_vars; ++j) {
          table[i][j] -= factor * table[pivot_row][j];
        }
      }
    }
  }

  for (int i = 0; i < num_constraints; ++i) {
    if (table[i].back() < -EPS) {
      std::cout << "The problem is infeasible." << std::endl;
      return;
    }
  }

  std::vector<double> x_opt(num_vars, 0);
  for (int j = 0; j < num_vars; ++j) {
    bool is_basic = true;
    int basic_row = -1;

    for (int i = 0; i < num_constraints; ++i) {
      if (std::abs(table[i][j] - 1.0) < EPS) {
        if (basic_row == -1) {
          basic_row = i;
        } else {
          is_basic = false;
          break;
        }
      } else if (std::abs(table[i][j]) > EPS) {
        is_basic = false;
        break;
      }
    }

    if (is_basic && basic_row != -1) {
      x_opt[j] = table[basic_row].back();
    }
  }

  double z_opt = table.back().back();

  std::cout << std::fixed << std::setprecision(static_cast<int>(epsilon));
  std::cout << "Optimal solution:" << std::endl;
  std::cout << "x* = [";
  for (int i = 0; i < num_vars; ++i) {
    std::cout << x_opt[i] << (i == num_vars - 1 ? "" : ", ");
  }
  std::cout << "]" << std::endl;
  std::cout << "z* = " << z_opt << std::endl << std::endl;
}
