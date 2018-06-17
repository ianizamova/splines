#pragma once
#include <vector>
#include <math.h>

// некие общие функции, которые должны быть вне классов

// ещё надо написать про решение квадратного уравнения
std::vector<double> solveQuadraticEq(double A, double B, double C);

// функция для метода Ньютона
double f_spline_coeffs(double a, double b, double c, double d, double w);
// производная для метода Ньютона
double fd_spline_coeffs(double a, double b, double c, double w);

// будем находить пересечение двух полиномов 3 степени методом Ньютона
double f_splineIntersection(double a, double b, double c, double d);