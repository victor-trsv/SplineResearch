#include <iostream>
#include <cmath>
#include <iomanip>
#include "GridCreator.h"
#include "Spline_3.h"
#include "FiniteDiff.h"
#include "Analysis.h"

double testFunction(double x) {
    return std::sin(x);
}

double testFunctionDeriv(double x) {
    return std::cos(x);
}

double testFunctionDeriv2(double x) {
    return -std::sin(x);
}

int main() {

    setlocale(LC_ALL, "Russian");

    double a = 0.07;
    double b = 0.24;
    double epsilon = 0.001;

    std::cout << "a = " << a << ", b = " << b << ", eps = " << epsilon << "\n\n";

    int n = 10;
    double r = 1.3;

    std::cout << "Равномерная сетка на отрезке [" << a << ", " << b << "]:\n";
    auto uniform = Com_Methods::GridGenerator::GenerateUniformGrid(a, b, n);
    for (double x : uniform) {
        std::cout << std::fixed << std::setprecision(6) << x << " ";
    }
    std::cout << "\n\n";

    std::cout << "Адаптивная сетка (r = " << r << "):\n";
    auto adaptive = Com_Methods::GridGenerator::GenerateAdaptiveGrid(a, b, n, r);
    for (double x : adaptive) {
        std::cout << std::fixed << std::setprecision(6) << x << " ";
    }
    std::cout << "\n\n";

    Research::conductSplineResearch(a, b, testFunction, testFunctionDeriv, testFunctionDeriv2);

    double center = (a + b) / 2;

    double exact_deriv = testFunctionDeriv(center);

    std::cout << "Центральная точка: " << center << "\n";
    std::cout << "Точное значение производной: " << exact_deriv << "\n";

    return 0;
}
