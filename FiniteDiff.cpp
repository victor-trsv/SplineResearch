#include "FiniteDiff.h"
#include <cmath>

double FiniteDifference::centralDifference(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double FiniteDifference::optimalStepDifference(double (*f)(double), double x, double epsilon) {
    double h = 0.5;
    double best_result = FiniteDifference::centralDifference(f, x, h);
    double best_error = epsilon + 1;

    int max_iterations = 10;

    for (int i = 0; i < max_iterations; i++) {
        double current_result = FiniteDifference::centralDifference(f, x, h);
        double next_result = FiniteDifference::centralDifference(f, x, h / 2);

        double error_estimate = std::abs(next_result - current_result);

        if (error_estimate < best_error) {
            best_error = error_estimate;
            best_result = next_result;
        }

        if (error_estimate < epsilon) {
            break;
        }

        h /= 2;
    }

    return best_result;
}
