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

	spline_coeffs& operator-( const spline_coeffs& other)
	{
		return spline_coeffs(a_ - other.a_, b_ - other.b_, c_ - other.c_, d_ - other.d_);
	}

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
	double a0_, a1_, a2_, a3_;
	hermitSplineCoeffs() : a0_(0), a1_(0), a2_(0), a3_(0) {};
	hermitSplineCoeffs(double a0, double a1, double a2, double a3) : a0_(a0), a1_(a1), a2_(a2), a3_(a3) {};

	hermitSplineCoeffs operator-(const hermitSplineCoeffs& other)
	{
		return hermitSplineCoeffs(a0_ - other.a0_, a1_ - other.a1_, a2_ - other.a2_, a3_ - other.a3_);
	}

};


// определим названия типов, чтобы было удобнее 
typedef std::vector<std::pair<double, double>> point_vec;
typedef std::map<double, point> x_y_t;
typedef std::map<double, double> r_t;
typedef std::vector<t_x_y> parametric_line;
typedef std::vector<t_r> radius_vector;

