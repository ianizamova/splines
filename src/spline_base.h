#pragma once
#include "curve.h"

class Spline : public Curve
{

public:
	Spline() {};
	Spline(const x_y_t& points, const r_t& rv_t) : Curve(points, rv_t) {};

	// в этом классе не будет реализации, будут только реализации для определенных видов сплайнов
	virtual  void MakeSpline() = 0;
	// найти точки пересечения с параметрически заданной кривовй
	virtual point_vec findIntersection(const Curve& other_curve) = 0;
	// найти точки пересечения с другим сплайном
	virtual point_vec findIntersection(const Spline& other_spline) = 0;
};

