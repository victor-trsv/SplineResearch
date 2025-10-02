#include "GridCreator.h"
#include <vector>

namespace Com_Methods {
    std::vector<double> GridGenerator::GenerateUniformGrid(double a, double b, int segments) {
        std::vector<double> grid;
        double h = (b - a) / segments;
        for (int i = 0; i <= segments; i++) {
            grid.push_back(a + i * h);
        }
        return grid;
    }

    std::vector<double> GridGenerator::GenerateAdaptiveGrid(double a, double b, int segments, double r) {
        std::vector<double> grid;

        if (fabs(r - 1.0) < 1e-10) {
            return GenerateUniformGrid(a, b, segments);
        }

        double h1 = (b - a) * (1 - r) / (1 - pow(r, segments));
        grid.push_back(a);

        double current = a;
        for (int i = 0; i < segments; i++) {
            current += h1 * pow(r, i);
            grid.push_back(current);
        }

        return grid;
    }
}
