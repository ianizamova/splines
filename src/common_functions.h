#pragma once
#include <vector>
#include "structs_types.h"
#include "curve.h"

// некие общие функции, которые должны быть вне классов

// ещё надо написать про решение квадратного уравнения
std::vector<double> solveQuadraticEq(double A, double B, double C);

// функция для метода Ньютона
double f_spline_coeffs(double a, double b, double c, double d, double w);
// производная для метода Ньютона
double fd_spline_coeffs(double a, double b, double c, double w);

// будем находить пересечение двух полиномов 3 степени методом Ньютона
double f_splineIntersection(double a, double b, double c, double d);
// маленькая функция для получения параметра на отрезке
double f_w(double t, double t1, double t2);
// поиск пересечения отрезков
std::vector<point> findSegmentIntersection(double x1, double y1, double a1, double b1, double x2, double y2, double a2, double b2);
// поиск пересечения кривых
std::vector<point> findCurvesIntersection(const Curve& c1, const Curve& c2);