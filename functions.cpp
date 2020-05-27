#include "functions.h"

double f1(double x) {
  return std::pow(2, x) + 1;
}

double df1(double x) {
  return std::pow(2, x) * std::log(2);
}

double ddf1(double x) {
  return std::pow(2, x) * std::log(2) * std::log(2);
}

double f2(double x) {
  return std::pow(x, 5);
}

double df2(double x) {
  return 5 * std::pow(x, 4);
}

double ddf2(double x) {
  return 20 * std::pow(x, 3);
}

double f3(double x) {
  return (1 - x) / 3;
}

double df3(double x) {
  return - 1 / 3.0;
}

double ddf3(double x) {
  return 0;
}
