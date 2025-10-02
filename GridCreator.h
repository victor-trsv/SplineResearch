#pragma once
#include <vector>
#include <cmath>

namespace Com_Methods {
    class GridGenerator {
    public:
        static std::vector<double> GenerateUniformGrid(double a, double b, int segments);
        static std::vector<double> GenerateAdaptiveGrid(double a, double b, int segments, double r);
    };
}
