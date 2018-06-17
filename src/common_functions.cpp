#include "common_functions.h"

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
		else if (D == 0)
		{
			x = -B / (2 * A);
			roots.push_back(x);
		}
		else
		{
			x = (-B + sqrt(D)) / (2 * A);
			roots.push_back(x);
			x = (-B - sqrt(D)) / (2 * A);
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
		if (abs(w1 - w) <= eps) return w;
		w = w1;
	}

	return w1;
}