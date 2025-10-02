#pragma once
#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>
#include <functional>

class Research {
public:
    static void conductSplineResearch(double a, double b,
        std::function<double(double)> func,
        std::function<double(double)> func_deriv,
        std::function<double(double)> func_deriv2);

    static double calculateMaxError(const std::vector<double>& points,
        std::function<double(double)> exact_func,
        std::function<double(double)> approx_func);
};

#endif
