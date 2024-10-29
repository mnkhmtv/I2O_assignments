#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;
const double EPS = 1e-6;

void print_problem(const vector<double>& C, const vector<vector<double>>& A, const vector<double>& b) {
    int num_vars = C.size();
    int num_constraints = A.size();

    cout << "Optimization problem:" << endl;
    cout << "max z = ";
    for (int i = 0; i < num_vars; ++i) {
        cout << C[i] << " * x" << (i + 1);
        if (i < num_vars - 1) cout << " + ";
    }
    cout << endl;

    cout << "subject to the constraints:" << endl;
    for (int i = 0; i < num_constraints; ++i) {
        for (int j = 0; j < num_vars; ++j) {
            cout << A[i][j] << " * x" << (j + 1);
            if (j < num_vars - 1) cout << " + ";
        }
        cout << " <= " << b[i] << endl;
    }
    cout << endl;
}

void simplex(vector<double> C, vector<vector<double>> A, vector<double> b, double epsilon) {
    int num_vars = C.size();
    int num_constraints = A.size();
    int total_vars = num_vars + num_constraints;
    vector<vector<double>> table(num_constraints + 1, vector<double>(total_vars + 1, 0));
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
        if (pivot_col == -1) break;

        int pivot_row = -1;
        double min_ratio = numeric_limits<double>::infinity();
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
            cout << "The problem is unbounded." << endl;
            return;
        }

        double pivot_val = table[pivot_row][pivot_col];
        for (double& val : table[pivot_row]) {
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
            cout << "The problem is infeasible." << endl;
            return;
        }
    }

    vector<double> x_opt(num_vars, 0);
    for (int j = 0; j < num_vars; ++j) {
        bool is_basic = true;
        int basic_row = -1;

        for (int i = 0; i < num_constraints; ++i) {
            if (abs(table[i][j] - 1.0) < EPS) {
                if (basic_row == -1) {
                    basic_row = i;
                } else {
                    is_basic = false;
                    break;
                }
            } else if (abs(table[i][j]) > EPS) {
                is_basic = false;
                break;
            }
        }

        if (is_basic && basic_row != -1) {
            x_opt[j] = table[basic_row].back();
        }
    }

    double z_opt = table.back().back();

    cout << fixed << setprecision(static_cast<int>(epsilon));
    cout << "Optimal solution:" << endl;
    cout << "x* = [";
    for (int i = 0; i < num_vars; ++i) {
        cout << x_opt[i] << (i == num_vars - 1 ? "" : ", ");
    }
    cout << "]" << endl;
    cout << "z* = " << z_opt << endl << endl;
}

int main() {
    double epsilon = 2;

    cout << "Example 1: " << endl;
    vector<double> C1 = {3, 2};
    vector<vector<double>> A1 = {
        {1, 1},
        {1, 0},
        {0, 1}
    };
    vector<double> b1 = {4, 2, 3};
    simplex(C1, A1, b1, epsilon);

    cout << "Example 2: " << endl;
    vector<double> C2 = {2, 3, 4};
    vector<vector<double>> A2 = {
        {1, 1, 1},
        {2, 4, 2},
        {1, 3, 0}
    };
    vector<double> b2 = {10, 20, 12};
    simplex(C2, A2, b2, epsilon);

    cout << "Example 3:" << endl;
    vector<double> C3 = {1, 1};
    vector<vector<double>> A3 = {
        {1, 0},
        {0, 1},
        {1, 1}
    };
    vector<double> b3 = {-1, -1, -10};
    simplex(C3, A3, b3, epsilon);

    cout << "Example 4: " << endl;
    vector<double> C5 = {2, 1};
    vector<vector<double>> A5 = {
        {1, -1},
        {2, 0}
    };
    vector<double> b5 = {10, 40};
    simplex(C5, A5, b5, epsilon);

    return 0;
}
