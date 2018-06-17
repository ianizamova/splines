#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>

// полезные структуры
struct spline_coeffs
{
	double a_, b_, c_, d_;
	spline_coeffs() : a_(0), b_(0), c_(0), d_(0) {};
	spline_coeffs(double a, double b, double c, double d) : a_(a), b_(b), c_(c), d_(d) {};
};

// параметрически заданная функция в точке x(t), y(t)
struct t_x_y
{
	double t, x, y;
};

// радиус-вектор r(t)
struct t_r
{
	double t, r;
};

struct point
{
	double x, y;
};
// коэффициенты эрмитова сплайна степени 3
struct hermitSplineCoeffs
{
	double a0, a1, a2, a3;
};


// определим названия типов, чтобы было удобнее 
typedef std::vector<std::pair<double, double>> point_vec;

typedef std::map<double, point> x_y_t;
typedef std::map<double, double> r_t;
typedef std::vector<t_x_y> parametric_line;
typedef std::vector<t_r> radius_vector;

