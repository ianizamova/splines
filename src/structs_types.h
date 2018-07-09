#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>
#include <functional>

struct point
{
	double x_, y_;
	point(): x_(0.0), y_(0.0) {};
	point(double x, double y) : x_(x), y_(y) {};
	point(const std::pair<double, double>& p) : x_(p.first), y_(p.second) {}
};


// коэффициенты сплайна степени 3
struct hermitSplineCoeffs 
{
	double a0_, a1_, a2_, a3_;
	hermitSplineCoeffs() : a0_(0), a1_(0), a2_(0), a3_(0) {};
	hermitSplineCoeffs(double a0, double a1, double a2, double a3) : a0_(a0), a1_(a1), a2_(a2), a3_(a3) {};
	
};


// определим названия типов, чтобы было удобнее 
typedef std::map<double, point> x_y_t;
typedef std::map<double, double> r_t;

typedef std::vector<std::pair<double, double>> f_t;
typedef std::vector<std::pair<double, point>> bpoints;

typedef std::vector<std::pair<double, hermitSplineCoeffs>> vec_coeffs_herm;

