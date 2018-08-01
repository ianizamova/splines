#include "common_functions.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <numeric>
#include <limits>
//#include <cassert>
#include <set>



// функции для печати
template< class T >
void print_set (const std::set<T>& s)
{
	std::cout << "[ ";
	for(auto i: s)
	{
		std::cout << i << " ";
	}
	std::cout << "]"<< std::endl;
}

template< class T >
void print_vec (const std::vector<T>& v)
{
	std::cout << "[ ";
	for(auto i: v)
	{
		std::cout << i << " ";
	}
	std::cout << "]"<< std::endl;
}
template< class T, class U >
void print_pair (const std::pair<T, U>& p)
{
	std::cout << "[ " << p.first << ", " <<p.second << "]"<< std::endl;
}

bool operator==(const point& lhs, const point& rhs)
{
	return (rhs.x_ == lhs.x_)&&(rhs.y_ == lhs.y_);
};

// функция для расчета значения w на отрезке [0,1]
double f_w(double t, double t1, double t2)
{
	if (std::abs(t2 - t1) > std::numeric_limits<double>::min()) 	return (t - t1) / (t2 - t1);
	else return 0.0;
}
// поиск пересечения отрезков
std::vector<point> findSegmentIntersection(const point& p1, const point& q1, const point& p2, const point& q2)
{
	std::vector<point> res;
	double x1 = p1.x_;
	double y1 = p1.y_;
	double a1 = q1.x_;
	double b1 = q1.y_;
	double x2 = p2.x_;
	double y2 = p2.y_;
	double a2 = q2.x_;
	double b2 = q2.y_;

	double t1, t2;
	double t1_chisl, t1_znam, t2_chisl, t2_znam;
	t1_chisl = (x2 - a2)*(y1 - y2) - (x1 - x2)*(y2 - b2);
	t1_znam = (x2 - a2)*(y1 - b1) - (x1 - a1)*(y2 - b2);

	t2_chisl = (x2 - a2)*(y1 - y2) - (x1 - x2)*(y2 - b2);
	t2_znam = (x2 - a2)*(y1 - b1) - (x1 - a1)*(y2 - b2);

	if (std::abs(t1_znam) <= std::numeric_limits<double>::min() ||
		std::abs(t2_znam) <= std::numeric_limits<double>::min()) 
	{
		return res;
	}

	t1 = t1_chisl / t1_znam;
	t2 = t2_chisl / t2_znam;


	if ((t1 >= 0.0 && t1 <= 1.0) && (t2 >= 0.0 && t2 <= 1.0))
	{
		double x_res, y_res;

		x_res = x1*(1.0 - t1) + t1*a1;
		y_res = y1*(1.0 - t1) + t1*b1;

		res.push_back(point(x_res, y_res));
		res.push_back(point(t1, t2));
	}

	return res;
}

// поиск пересечения кривых
std::vector<point> findCurvesIntersection(const Curve& curve1, const Curve& curve2, double epsilon, size_t iter_max)
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
			//std::cout<< "p2: [ "<< igrid2[j].second.x_ <<", "<<igrid2[j].second.y_ << "]"<<std::endl;
			point q2(igrid2[j + 1].second.x_, igrid2[j + 1].second.y_);
			//std::cout<< "q2: [ "<< igrid2[j+1].second.x_ <<", "<<igrid2[j+1].second.y_ << "]"<<std::endl;

			size_t seg_num1, seg_num2; // номера отрезков базовой сетки для определения функций
			seg_num1 = curve1.getBaseI(i); // номер базового отрезка на первой кривой
			seg_num2 = curve2.getBaseI(j); // номер базового отрезка на второй кривой
			
			std::vector<point> first_approx = findSegmentIntersection(p1, q1, p2, q2);

			// iteration method
			if (first_approx.size() > 0)
			{
				point intersec_point;
				intersec_point = metodNewton(curve1, curve2, epsilon, first_approx.at(1), seg_num1, seg_num2, iter_max);
			}
			// иначе линии не пересекаются

		}
	}

	return res;
}


// поиск пересечения двух параметрических кривых методом Ньютона
point metodNewton(const Curve& curve1, const Curve& curve2, double eps, point start_point, size_t i1, size_t i2, size_t iter_max)
{
	point res;
	// координаты стартовой точки
	double t1_start = start_point.x_; 
	double t2_start = start_point.y_;
	// начальные значения х и у
	double x1_start = curve1.x_t(t1_start, i1);
	double x2_start = curve2.x_t(t2_start, i2);
	double y1_start = curve1.y_t(t1_start, i1);
	double y2_start = curve2.y_t(t2_start, i2);

	double residual_x1, residual_y1; // невязки по х и у
	double residual_x2, residual_y2; // невязки по х и у
	
	double dx, dy;
	residual_x1 = residual_x2 = eps + 10.0*eps; // большое начальное значение невязки
	residual_y1 = residual_y2 = eps + 10.0*eps;

	double t1_new, t2_new;
	double x1_new, x2_new;
	double y1_new, y2_new;

	double dt1, dt2;

	size_t iter_num = 0; 
	while (residual_x1 > eps || residual_y1 > eps || residual_x2 > eps || residual_y2 > eps )
	{
		double fx = curve1.x_t(t1_start, i1) - curve2.x_t(t2_start, i2);
		double dfx = curve1.xdt_t(t1_start, i1) - curve2.xdt_t(t2_start, i2);

		double fy = curve1.y_t(t1_start, i1) - curve2.y_t(t2_start, i2);
		double dfy = curve1.ydt_t(t1_start, i1) - curve2.ydt_t(t2_start, i2);

		// рассчитаем коэффииициенты матрицы
		double a11 = curve1.xdt_t(t1_start, i1);   // df1/dt1
		double a12 = -curve2.xdt_t(t2_start, i2);  // df1/dt2

		double a21 = curve1.ydt_t(t1_start, i1); // df2/dt1
		double a22 = -curve2.ydt_t(t2_start, i2); // df2/dt2

		// правая часть
		double b1 = -fx;  // x1(t1) - x2(t2)
		double b2 = -fy;  // y1(t1) - y2(t2)

		// проверить определитель
		double detA = a11*a22 - a12*a21;
		if (std::abs(detA) <= std::numeric_limits<double>::min())  // определитель равен нулю, получается, что решений нет
		{
			return res; // что-то сделать
			std::cout << "Det A == 0!!!" << std::endl;
			// TODO нужно решать систему скалярных уравнений
		}
		else
		{
			dt1 = (a22 * b1 - a12 * b2) / detA;
			dt2 = (-a21 * b1 + a11 * b2) / detA;

			t1_new = t1_start + dt1;
			t2_new = t2_start + dt2;
			
			// пересчитать х и у
			x1_new = curve1.x_t(t1_new, i1);
			x2_new = curve2.x_t(t2_new, i2);

			y1_new = curve1.y_t(t1_new, i1);
			y2_new = curve2.y_t(t2_new, i2);

			residual_x1 = std::abs(x1_new - x1_start);
			residual_x2 = std::abs(x2_new - x2_start);
			residual_y1 = std::abs(y1_new - y1_start);
			residual_y2 = std::abs(y2_new - y2_start);

			if (residual_x1 <= eps && residual_y1 <= eps &&
					residual_x2 <= eps && residual_y2 <= eps )
			{
				return point(x1_new, y1_new);
			}
			t1_start = t1_new;
			t2_start = t2_new;

			x1_start = x1_new;
			x2_start = x2_new;

			y1_start = y1_new;
			y2_start = y2_new;

		}

		++iter_num;
		if(iter_num > iter_max) return point(x1_new, y1_new);
		
	}

	return point( x1_new, y1_new );  // по идее, можно возвращать только одну точку, потому что при сходимости значения должны быть одинаковые
}

