#pragma once
#include <vector>
#include <utility>
#include <set>

#include "structs_types.h"
#include "curve.h"

// некие общие функции, которые должны быть вне классов
template< class T >
void print_set (const std::set<T>& s);
template< class T >
void print_vec (const std::vector<T>& v);
template< class T, class U >
void print_pair (const std::pair<T, U>& p);

bool operator==(const point& lhs, const point& rhs);

// функция для метода Ньютона
double f_spline_coeffs(double a, double b, double c, double d, double w);
// производная для метода Ньютона
double fd_spline_coeffs(double a, double b, double c, double w);

// будем находить пересечение двух полиномов 3 степени методом Ньютона
double f_splineIntersection(double a, double b, double c, double d);
// маленькая функция для получения параметра на отрезке
double f_w(double t, double t1, double t2);
// построение внутренней сетки
void makeInnerGrid(Curve& curve);

// поиск пересечения отрезков
std::vector<point> findSegmentIntersection(const point& p1, const point& q1, const point& p2, const point& q2);

// поиск пересечения кривых
std::vector<point> findCurvesIntersection(const Curve& c1, const Curve& c2, double epsilon, size_t iter_max);

// поиск пересечения двух параметрических кривых методом Ньютона
point metodNewton(const Curve& curve1, const Curve& curve2, double eps, point start_point, size_t i1, size_t i2, size_t iter_max);
