﻿#include "common_functions.h"
#include "curve.h"
#include "structs_types.h"
#include "hermit_spline.h"


int main( int argc, char* argv[])
{
	// надо считать время
	double t_min, t_max, step;

	// вектор значений временных точек
	std::vector<double> vector_t;
	
	// для функций, заданных параметрически, построим сплайны 
	HermitSpline s1, s2;
	
	s1.readBasePoints(argv[1]);
	s2.readBasePoints(argv[2]);

	s1.MakeSpline();
	s2.MakeSpline();

	s1.findIntersection(s2);

	radius_vector rv = s1.findClosestPoints(s2);
	// 
	// и теперь найдём точки пересечения или просто ближайшие точки
	point_vec foundPoints = s1.findIntersection(s2);

	// или в идеале - делаем функцию не-член и вызываем её от двух объектов класса Curve
	// findIntersection(const Curve& c1, const Curve& c2);

	return 0;
}

