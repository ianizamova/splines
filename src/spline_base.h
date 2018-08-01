#pragma once
#include "curve.h"

class Spline : public Curve
{

public:
	Spline() {};
//	Spline(const bpoints& points): base_points_(points) {};

	// в этом классе не будет реализации, будут только реализации для определенных видов сплайнов
	virtual  void MakeSpline() {};
	virtual std::vector<hermitSplineCoeffs> GetCoeffs() const { return std::vector<hermitSplineCoeffs>({ { 0.0, 0.0, 0.0, 0.0 } }); };
	
	virtual double x_t(double t, size_t i) { return 0.0; };
	virtual double xdt_t(double t, size_t i) { return 0.0; };
	virtual double xdt2_t(double t, size_t i) { return 0.0; };
	virtual double y_t(double t, size_t i) { return 0.0; };
	virtual double ydt_t(double t, size_t i) { return 0.0; };
	virtual double ydt2_t(double t, size_t i) { return 0.0; };
};

