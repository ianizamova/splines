#include "common_functions.h"
#include <math.h>
#include <utility>
#include <numeric>
#include <limits>

// ещё надо написать про решение квадратного уравнения
std::vector<double> solveQuadraticEq(double A, double B, double C)
{
	std::vector<double> roots;
	double x, D;
	if (A == 0)
	{
		x = -C / B;
		roots.push_back(x);
	}
	else
	{
		D = B*B - 4 * A*C;
		if (D < 0) return roots;
		else if (std::abs(D) <= std::numeric_limits<double>::min())
		{
			x = -B / (2.0 * A);
			roots.push_back(x);
		}
		else
		{
			x = (-B + std::sqrt(D)) / (2 * A);
			roots.push_back(x);
			x = (-B - std::sqrt(D)) / (2 * A);
			roots.push_back(x);
		}
	}
	return roots;
}

// функция для метода Ньютона
double f_spline_coeffs(double a, double b, double c, double d, double w)
{
	return a*std::pow(w, 3) + b*std::pow(w, 2) + c*w + d;
}
// производная для метода Ньютона
double fd_spline_coeffs(double a, double b, double c, double w)
{
	return 3 * a*std::pow(w, 2) + 2 * b*w + c;
}

// будем находить пересечение двух полиномов 3 степени методом Ньютона
double f_splineIntersection(double a, double b, double c, double d)
{
	double w = 0; // 

	double eps = 1.e-9;
	size_t iter_max, iter_num;
	double w1, f, fd;
	w1 = 10;
	iter_num = 0;
	iter_max = 100;
	while (true)
	{
		f = f_spline_coeffs(a, b, c, d, w);
		fd = fd_spline_coeffs(a, b, c, w);

		w1 = w - f / fd;

		iter_num++;
		if (iter_num == iter_max) return w;
		if (std::abs(w1 - w) <= eps) return w;
		w = w1;
	}

	return w1;
}

double f_w(double t, double t1, double t2)
{
	if (t2 - t1 != 0.0) 	return (t - t1) / (t2 - t1);
	else return 0.0;
}

std::vector<point> findSegmentIntersection(double x1, double y1, double a1, double b1, double x2, double y2, double a2, double b2)
{
	std::vector<point> res;

	double t1, t2;
	double t1_chisl, t1_znam, t2_chisl, t2_znam;
	t1_chisl = (x2 - a2)*(y1 - y2) - (x1 - x2)*(y2 - b2);
	t1_znam = (x2 - a2)*(y1 - b1) - (x1 - a1)*(y2 - b2);

	t2_chisl = (x2 - a2)*(y1 - y2) - (x1 - x2)*(y2 - b2);
	t2_znam = (x2 - a2)*(y1 - b1) - (x1 - a1)*(y2 - b2);

	if (std::abs(t1_znam) <= std::numeric_limits<double>::min() || std::abs(t2_znam) <= std::numeric_limits<double>::min()) return res;

	t1 = t1_chisl / t1_znam;
	t2 = t2_chisl / t2_znam;


	if ((t1 >= 0.0 && t1 <= 1.0) && (t2 >= 0.0 && t2 <= 1.0))
	{
		double x_res, y_res;

		x_res = x1*(1.0 - t1) + t1*a1;
		y_res = y1*(1.0 - t1) + t1*b1;

		res.push_back(point(x_res, y_res));
	}

	return res;
}

std::vector<point> findCurvesIntersection(const Curve& curve1, const Curve& curve2)
{
	std::vector<point> res;
	//1. Loop in inner grid
	// all functions for curve1 and curve2
	// loop in the inner grid of curve1
	//(auto i = 0; i < curve1.i )

	bpoints igrid1 = curve1.GetInnerGrid();
	bpoints igrid2 = curve2.GetInnerGrid();

	//inner grid of curve1
	for (size_t i = 0; i < igrid1.size()-1; i++)
	{
		point p1(igrid1[i].second.x_, igrid1[i].second.y_);
		point q1(igrid1[i+1].second.x_, igrid1[i+1].second.y_);
		
		// inner grid of curve2
		for (size_t j = 0; j < igrid2.size()-1; j++)
		{
			// find first approximation
			// 1. 4 points x1,y1, a1,b1, x2,y2, a2,b2
			point p2(igrid2[j].second.x_, igrid2[j].second.y_);
			point q2(igrid2[j + 1].second.x_, igrid2[j + 1].second.y_);

			std::vector<point> first_approx = findSegmentIntersection(p1.x_, p1.y_, q1.x_, q1.y_, p2.x_, p2.y_, q2.x_, q2.y_);
			// iteration method
			if (first_approx.size() > 0)
			{

			}

		}
	}

	return res;
}
