#pragma once
#include <fstream>
#include <string>
#include <iostream>
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

// классы для коэффициентов прямой и параболы, пригодятся для тестов
struct straightLineCoeffs
{
	double k_, b_;
	straightLineCoeffs() : k_(0), b_(0) {};
	straightLineCoeffs(double k, double b) : k_(k), b_(b) {};
};

struct ellipsCoeffs
{
	double a_, b_;
	ellipsCoeffs() : a_(0), b_(0) {};
	ellipsCoeffs(double a, double b) : a_(a), b_(b) {};
};
///////////////////////////////////////////////

// определим названия типов, чтобы было удобнее 
typedef std::map<double, point> x_y_t;
typedef std::map<double, double> r_t;

typedef std::vector<std::pair<double, double>> f_t;
typedef std::vector<std::pair<double, point>> bpoints;

typedef std::vector<std::pair<double, hermitSplineCoeffs>> vec_coeffs_herm;
typedef std::vector<std::pair<double, straightLineCoeffs>> vec_coeffs_straight;
typedef std::vector<std::pair<double, ellipsCoeffs>> vec_coeffs_ellips;
