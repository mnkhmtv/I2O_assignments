#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

// Function to perform the bisection method
double bisection_method(function<double(double)> f, double a, double b, double tolerance) {
    // Check for invalid input: ensure the root lies in the interval
    if (f(a) * f(b) > 0) {
        cout << "Invalid since function must have opposite signs at the ends of the interval" << endl;
        return NAN;
    }

    double c; // Midpoint of the interval
    int iteration = 1;

    // Repeat until the interval width is smaller than the tolerance
    while ((b - a) / 2 > tolerance) {
        c = (a + b) / 2;

        // Debug output for each iteration
        cout << "Iteration " << iteration << ": Interval = [" << a << ", " << b
             << "], c = " << c << ", f(c) = " << f(c) << endl;

        // Check if the midpoint is the root or meets the tolerance condition
        if (fabs(f(c)) < tolerance) {
            return c; // Approximate root found
        }

        // Narrow down the interval based on the sign of f(c)
        if (f(c) * f(a) < 0) {
            b = c;
        } else if (f(c) * f(b) < 0) { // Ensure refinement is balanced
            a = c;
        } else {
            // If both endpoints are roots, stop at midpoint
            break;
        }

        iteration++;
    }

    // Return the midpoint of the final interval as the approximate root
    return (a + b) / 2;
}

double f(double x) {
    return pow(x, 3) - 6 * pow(x, 2) + 11 * x - 6;}

int main() {
    double a, b, tolerance;
    
    cout << "Enter the lower bound of the interval (a): ";
    cin >> a;
    cout << "Enter the upper bound of the interval (b): ";
    cin >> b;
    cout << "Enter the tolerance (epsilon): ";
    cin >> tolerance;
    double root = bisection_method(f, a, b, tolerance);
    
    if (!isnan(root)) {
        cout << "Approximate root: " << root << endl;
    }

    return 0;
}
