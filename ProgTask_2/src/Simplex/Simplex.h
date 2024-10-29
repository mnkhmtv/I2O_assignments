// Simplex.h
#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

const double EPS = 1e-6;

void print_problem(const std::vector<double> &C,
                   const std::vector<std::vector<double>> &A,
                   const std::vector<double> &b);

void simplex(std::vector<double> C, std::vector<std::vector<double>> A,
             std::vector<double> b, double epsilon);

#endif // SIMPLEX_H
