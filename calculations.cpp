#include "calculations.h"

const double kEpsilon = 1e-7;

double FindRoot(double (*first)(double x),
                double (*dfirst)(double x),
                double (*ddfirst)(double x),
                double (*second)(double x),
                double (*dsecond)(double x),
                double (*ddsecond)(double x),
                double lhs,
                double rhs) {
  if ((dfirst((rhs + lhs) / 2) - dsecond((rhs + lhs) / 2)) * (ddfirst((rhs + lhs) / 2) - ddsecond((rhs + lhs) / 2)) > 0) {
    // chords from left, tangents from right
    while (std::fabs(rhs - lhs) > kEpsilon) {
      lhs = lhs - ((first(lhs) - second(lhs)) * (rhs - lhs)) /
                  (first(rhs) - second(rhs) - first(lhs) + second(lhs));
      rhs = rhs - (first(rhs) - second(rhs)) /
                  (dfirst(rhs) - dsecond(rhs));
    }
  } else {
    // chords from right, tangents from left
    while (std::fabs(rhs - lhs) > kEpsilon) {
      lhs = lhs - (first(lhs) - second(lhs)) /
                  (dfirst(lhs) - dsecond(lhs));
      rhs = rhs - ((first(rhs) - second(rhs)) * (rhs - lhs)) /
                  (first(rhs) - second(rhs) - first(lhs) + second(lhs));
    }
  }
  return (rhs + lhs) / 2;
}


double FindIntegral(double (*func)(double x), double lhs, double rhs) {
  int n = 128;
  double prev = (func(lhs) + func(rhs)) / 2 + kEpsilon * 10;
  double now = prev - kEpsilon * 10;

  for (double i = lhs + (rhs - lhs) / n; i < rhs; i += (rhs - lhs) / n) {
    now += func(i);
  }
  now *= (rhs - lhs) / n;

  n <<= 1;

  while (std::fabs(prev - now) > kEpsilon) {
    prev = now;

    now = (func(lhs) + func(rhs)) / 2;
    for (double i = lhs + (rhs - lhs) / n; i < rhs; i += (rhs - lhs) / n) {
      now += func(i);
    }
    now *= (rhs - lhs) / n;

    n <<= 1;
  }
  return now;
}


double FindArea(double (*first)(double x),
                double (*dfirst)(double x),
                double (*ddfirst)(double x),
                double (*second)(double x),
                double (*dsecond)(double x),
                double (*ddsecond)(double x),
                double (*third)(double x),
                double (*dthird)(double x),
                double (*ddthird)(double x)) {
  double x1 = FindRoot(first, dfirst, ddfirst, third, dthird, ddthird, -3, -2);
  double x2 = FindRoot(second, dsecond, ddsecond, third, dthird, ddthird, 0.6, 0.7);
  double x3 = FindRoot(first, dfirst, ddfirst, second, dsecond, ddsecond, 1.2, 1.4);

  return FindIntegral(first, x1, x3) - FindIntegral(third, x1, x2) - FindIntegral(second, x2, x3);
}
