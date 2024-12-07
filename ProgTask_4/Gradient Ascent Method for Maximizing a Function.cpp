#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//f(x) = -x^2 + 4x + 1
double f(double x) {
    return -x * x + 4 * x + 1;
}

// Derivative of f
double grad_f(double x) {
    return -2 * x + 4;
}

// Gradient Ascent Method
double gradient_ascent(double (*f)(double), double (*grad_f)(double), double x0, double alpha, int max_iterations) {
    double x = x0; // Initialize x with the initial guess

    for (int i = 0; i < max_iterations; ++i) {
        double gradient = grad_f(x); // Compute the gradient
        cout << "Iteration " << i + 1 << ": x = " << x << ", f(x) = " << f(x) << ", f'(x) = " << gradient << endl;

        // Update x using the Gradient Ascent formula
        x = x + alpha * gradient;

        
    }

    return x;
}

int main() {
    // Input parameters
    double x0, alpha;
    int max_iterations;

    cout << "enter initial guess (x0): ";
    cin >> x0;
    cout << "Enter learning rate alpha: ";
    cin >> alpha;
    cout << "Enter number of iterations (N): ";
    cin >> max_iterations;

    // Gradient Ascent
    double x_max = gradient_ascent(f, grad_f, x0, alpha, max_iterations);
    double f_max = f(x_max);

    cout << fixed << setprecision(6);
    cout << "\nApproximate maximum point: x = " << x_max << endl;
    cout << "Maximum value of f(x): f(x) = " << f_max << endl;

    return 0;
}
