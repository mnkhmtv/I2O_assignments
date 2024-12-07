#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x) {
    return (x - 2) * (x - 2) + 3;
}

// Golden Section Method
void golden_section_method(double a, double b, double tolerance) {
    const double phi = 0.618; // Golden ratio constant
    double lambda, mu;        // Points to evaluate
    double f_lambda, f_mu;    // Function values at lambda and mu

    //cout << fixed << setprecision(5);

    while ((b - a) >= tolerance) {
        lambda = a + (1 - phi) * (b - a);
        mu = a + phi * (b - a);

        f_lambda = f(lambda);
        f_mu = f(mu);

        if (f_lambda < f_mu) {
            b = mu; // Update b
        } else {
            a = lambda; // Update a
        }
    }

    // Final result
    double xmin = (a + b) / 2;
    double fmin = f(xmin);
    cout << "Approximate minimum point: xmin = " << xmin << endl;
    cout << "Minimum value of f(x): f(xmin) = " << fmin << endl;
}

int main() {
    double a, b, tolerance;
    cout << "Enter the interval in format:a b: ";
    cin >> a >> b;
    cout << "Enter the tolerance (e.g. 1e-4): ";
    cin >> tolerance;

    golden_section_method(a, b, tolerance);

    return 0;
}
