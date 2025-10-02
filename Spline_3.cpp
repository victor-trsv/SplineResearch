#include "Spline_3.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;


Spline3::Spline3(const vector<double>& x_, const vector<double>& y_)
    : x(x_), y(y_) {

    n = x.size() - 1;
    a = y;
    b.resize(n);
    c.resize(n + 1);
    d.resize(n);

    std::vector<double> h(n);
    for (int i = 0; i < n; i++) {
        h[i] = x[i + 1] - x[i];
    }

    std::vector<double> alpha(n);
    for (int i = 1; i < n; i++) {
        alpha[i] = (3.0 / h[i]) * (a[i + 1] - a[i]) - (3.0 / h[i - 1]) * (a[i] - a[i - 1]);
    }

    std::vector<double> l(n + 1), mu(n + 1), z(n + 1);
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for (int i = 1; i < n; i++) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    for (int j = n - 1; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }
}

double Spline3::evaluate(double X) const {
    int i = 0;
    for (int j = 0; j < n; j++) {
        if (X >= x[j] && X <= x[j + 1]) {
            i = j;
            break;
        }
    }
    double dx = X - x[i];
    return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
}

double Spline3::derivative(double X) const {
    int i = 0;
    for (int j = 0; j < n; j++) {
        if (X >= x[j] && X <= x[j + 1]) {
            i = j;
            break;
        }
    }
    double dx = X - x[i];
    return b[i] + 2 * c[i] * dx + 3 * d[i] * dx * dx;
}

double Spline3::derivative_2(double X) const {
    int i = 0;
    for (int j = 0; j < n; j++) {
        if (X >= x[j] && X <= x[j + 1]) {
            i = j;
            break;
        }
    }
    double dx = X - x[i];
    return 2 * c[i] + 6 * d[i] * dx;
}
