#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include "structs_types.h"

// классы. самый базовый класс - кривая. Просто параметрически заданная линия, у неё есть базовые точки и  радиус-вектор r(t)
class Curve
{
	parametric_line curve;
	radius_vector r_vec;

	x_y_t points_;  // map
	r_t rv_t_;  //map

public:

	Curve() {};
	Curve(const x_y_t& points, const r_t& rv_t)
	{
		points_ = points;
		rv_t_ = rv_t;
	};


	// векторы
	parametric_line GetCurve() const
	{
		return curve;
	};
	radius_vector GetRVec() const
	{
		return r_vec;
	}

	//map
	x_y_t GetPoints()
	{
		return points_;
	};
	//map
	r_t GetRvect()
	{
		return rv_t_;
	};

	// поиск пересечения с другой кривой, заданной опорными точками
	point_vec findBasePointsIntersection(const Curve& other_curve);
	virtual point_vec findIntersection(const Curve& other_curve);

	// чтение базовых точек из файла, построение кривой
	void readBasePoints(const std::string& filename);
	
};



