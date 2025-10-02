#pragma once
#ifndef FINITEDIFF_H
#define FINITEDIFF_H

class FiniteDifference {
public:
    static double centralDifference(double (*f)(double), double x, double h);
    static double optimalStepDifference(double (*f)(double), double x, double h);
};

#endif
