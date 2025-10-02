#pragma once
#include <vector>
class Spline3 {
private:
    std::vector<double> x, y;
    std::vector<double> a, b, c, d;
    int n;

public:
    Spline3(const std::vector<double>& x_, const std::vector<double>& y_);

    double evaluate(double X) const;
    double derivative(double X) const;
    double derivative_2(double X) const;
};
