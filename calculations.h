#ifndef CALCULATIONS_H
#define CALCULATIONS_H


#include "functions.h"


double FindRoot(double (*first)(double x),
                double (*dfirst)(double x),
                double (*ddfirst)(double x),
                double (*second)(double x),
                double (*dsecond)(double x),
                double (*ddsecond)(double x),
                double lhs,
                double rhs);


double FindIntegral(double (*func)(double x), double lhs, double rhs);


double FindArea(double (*first)(double x),
                double (*dfirst)(double x),
                double (*ddfirst)(double x),
                double (*second)(double x),
                double (*dsecond)(double x),
                double (*ddsecond)(double x),
                double (*third)(double x),
                double (*dthird)(double x),
                double (*ddthird)(double x));


#endif // CALCULATIONS_H
