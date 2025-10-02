#include "Analysis.h"
#include "GridCreator.h"
#include "Spline_3.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

void Research::conductSplineResearch(double a, double b,
    std::function<double(double)> func,
    std::function<double(double)> func_deriv,
    std::function<double(double)> func_deriv2) {

    // Исходная сетка
    int n_base = 8;
    double h_base = (b - a) / n_base;

    std::vector<int> n_values = { n_base, 2 * n_base, 4 * n_base };
    std::vector<double> h_values = { h_base, h_base / 2, h_base / 4 };

    for (int level = 0; level < 3; level++) {
        int n = n_values[level];
        double h = h_values[level];

        std::cout << "Сетка с шагом h = " << h << " (n = " << n << " узлов):\n";

        // Создаем сетку и вычисляем значения функции
        auto grid = Com_Methods::GridGenerator::GenerateUniformGrid(a, b, n);
        std::vector<double> values(n + 1);
        for (int i = 0; i <= n; i++) {
            values[i] = func(grid[i]);
        }

        // Строим сплайн
        Spline3 spline(grid, values);

        // Точки для исследования (не совпадают с узлами)
        int test_points_count = 15;
        std::vector<double> test_points;
        for (int i = 0; i < test_points_count; i++) {
            double point = a + (i + 0.5) * (b - a) / test_points_count;
            test_points.push_back(point);
        }

        // Вычисляем ошибки
        std::vector<double> errors_func(test_points_count);
        std::vector<double> errors_deriv(test_points_count);
        std::vector<double> errors_deriv2(test_points_count);

        double max_error_func = 0, max_error_deriv = 0, max_error_deriv2 = 0;

        std::cout << std::setw(12) << "x" << std::setw(15) << "f(x)"
            << std::setw(15) << "S(x)" << std::setw(15) << "Ошибка f"
            << std::setw(15) << "f'(x)" << std::setw(15) << "S'(x)"
            << std::setw(15) << "Ошибка f'\n";

        for (int i = 0; i < test_points_count; i++) {
            double x = test_points[i];
            double exact_func = func(x);
            double exact_deriv = func_deriv(x);
            double exact_deriv2 = func_deriv2(x);

            double spline_func = spline.evaluate(x);
            double spline_deriv = spline.derivative(x);
            double spline_deriv2 = spline.derivative_2(x);

            errors_func[i] = std::abs(exact_func - spline_func);
            errors_deriv[i] = std::abs(exact_deriv - spline_deriv);
            errors_deriv2[i] = std::abs(exact_deriv2 - spline_deriv2);

            max_error_func = std::max(max_error_func, errors_func[i]);
            max_error_deriv = std::max(max_error_deriv, errors_deriv[i]);
            max_error_deriv2 = std::max(max_error_deriv2, errors_deriv2[i]);

            if (i < 5) {
                std::cout << std::fixed << std::setprecision(6)
                    << std::setw(12) << x << std::setw(15) << exact_func
                    << std::setw(15) << spline_func << std::setw(15) << errors_func[i]
                    << std::setw(15) << exact_deriv << std::setw(15) << spline_deriv
                    << std::setw(15) << errors_deriv[i] << "\n";
            }
        }

        std::cout << "\nМаксимальные ошибки:\n";
        std::cout << "Функция: " << max_error_func << "\n";
        std::cout << "Первая производная: " << max_error_deriv << "\n";
        std::cout << "Вторая производная: " << max_error_deriv2 << "\n";
        std::cout << "----------------------------------------\n\n";
    }

    std::cout << "Сравнение с конечными разностями:\n";
    double x_center = (a + b) / 2;
    double exact_deriv = derivative(x_center);

    std::cout << "Центральная точка: x = " << x_center << "\n";
    std::cout << "Точное значение f'(" << x_center << ") = " << exact_deriv << "\n\n";

    h_values = { 0.7, 0.5, 0.1, 0.01, 0.005, 0.0025, 0.00125 };
    std::cout << std::setw(12) << "h" << std::setw(15) << "Правая разн."
        << std::setw(15) << "Левая разн." << std::setw(15) << "Центр. разн."
        << std::setw(15) << "Ошибка прав." << std::setw(15) << "Ошибка лев."
        << std::setw(15) << "Ошибка центр.\n";

    for (double h : h_values) {
        double right_diff = FiniteDifferenceDerivative(function, x_center, h, 0);
        double left_diff = FiniteDifferenceDerivative(function, x_center, h, 1);
        double central_diff = FiniteDifferenceDerivative(function, x_center, h, 2);

        double error_right = fabs(right_diff - exact_deriv);
        double error_left = fabs(left_diff - exact_deriv);
        double error_central = fabs(central_diff - exact_deriv);

        std::cout << std::setw(12) << h << std::setw(15) << right_diff
            << std::setw(15) << left_diff << std::setw(15) << central_diff
            << std::setw(15) << error_right << std::setw(15) << error_left
            << std::setw(15) << error_central << "\n";
    }
}

double Research::calculateMaxError(const std::vector<double>& points,
    std::function<double(double)> exact_func,
    std::function<double(double)> approx_func) {
    double max_error = 0;
    for (double x : points) {
        double error = std::abs(exact_func(x) - approx_func(x));
        if (error > max_error) max_error = error;
    }
    return max_error;
}
