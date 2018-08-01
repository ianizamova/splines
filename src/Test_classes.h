#include "common_functions.h"
#include "curve.h"
#include "structs_types.h"
#include "hermit_spline.h"
#include "test_runner.h"
#include <math.h>


class TestStraightLine : public Curve
{
	straightLineCoeffs coeffs_x_;
	straightLineCoeffs coeffs_y_;

public:
	TestStraightLine() {};

	TestStraightLine(const straightLineCoeffs& coeffs_x,const straightLineCoeffs& coeffs_y,
			const bpoints& points) :
		coeffs_x_(coeffs_x), coeffs_y_(coeffs_y), Curve(points) {};

	virtual double x_t(double t, size_t i) const override
	{
		return coeffs_x_.k_ * t + coeffs_x_.b_;
	};
	virtual double xdt_t(double t, size_t i) const override
	{
		return coeffs_x_.k_;
	};
	virtual double xdt2_t(double t, size_t i) const override
	{
		return 0.0;
	};
	virtual double y_t(double t, size_t i) const override
	{
		return coeffs_y_.k_ * t + coeffs_y_.b_;
	};
	virtual double ydt_t(double t, size_t i) const override
	{
		return  coeffs_y_.k_;
	};
	virtual double ydt2_t(double t, size_t i) const override
	{
		return 0.0;
	};

};

class TestEllips : public Curve
{
	ellipsCoeffs coeffs;

public:
	TestEllips() {};

	TestEllips(const ellipsCoeffs& coeffs_, const bpoints& points) :
		coeffs(coeffs_), Curve(points) {};

	virtual double x_t(double t, size_t i) const override
	{
		return coeffs.a_ * cos(t) ;
	};
	virtual double xdt_t(double t, size_t i) const override
	{
		return  - coeffs.a_* sin(t);
	};
	virtual double xdt2_t(double t, size_t i) const override
	{
		return  - coeffs.a_* cos(t);
	};
	virtual double y_t(double t, size_t i) const override
	{
		return coeffs.b_*sin( t);
	};
	virtual double ydt_t(double t, size_t i) const override
	{
		return  coeffs.b_ * cos(t);
	};
	virtual double ydt2_t(double t, size_t i) const override
	{
		return  - coeffs.b_ * sin(t);
	};
};

void TestCommonFunctions()
{
	
}

void TestHermitSplineConstructor()
{
	//default
	HermitSpline hs;
	
	//HermitSpline(const vec_coeffs_herm& coeffs_x, const vec_coeffs_herm& coeffs_y) : coeffs_x_(coeffs_x), coeffs_y_(coeffs_y)
	vec_coeffs_herm vx, vy;
	HermitSpline(vx, vy);

	//HermitSpline(const vec_coeffs_herm& coeffs_x, const vec_coeffs_herm& coeffs_y, constt bpoints& points)
	bpoints base;
	HermitSpline(vx, vy, base);
}

void TestEllipsConstructor()
{
	//default
	TestEllips el;

	//TestEllips(const vec_coeffs_ellips& coeffs_, const bpoints& points) :
	//coeffs(coeffs_), Curve(points) {};

	bpoints bp;
	ellipsCoeffs ec;
	TestEllips(ec, bp);

}

void TestStraightLineConstructor()
{
	//default
	TestStraightLine sl;

	//TestStraightLine(const straightLineCoeffs& coeffs_x,const straightLineCoeffs& coeffs_y,
	//const bpoints& points) :
	//coeffs_x_(coeffs_x), coeffs_y_(coeffs_y), Curve(points) {};
	bpoints bp;
	straightLineCoeffs cx, cy;

	TestStraightLine(cx, cy, bp);
}

