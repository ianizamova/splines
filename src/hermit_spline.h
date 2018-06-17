#pragma once
#include "spline_base.h"

class HermitSpline : public Spline
{
	// коэффициенты эрмитова сплайна
	std::vector<hermitSplineCoeffs> coeffs_;

public:
	HermitSpline() {};
	HermitSpline(const std::vector<hermitSplineCoeffs>& coeffs) : coeffs_(coeffs)
	{};

	HermitSpline(const std::vector<hermitSplineCoeffs>& coeffs, const x_y_t& points, const r_t& rv_t) : coeffs_(coeffs), Spline(points,rv_t)
	{};

	std::vector<hermitSplineCoeffs> GetCoeffs() const
	{
		return coeffs_;
	};

	// построить эрмитов сплайн
	void MakeSpline() override;

	point_vec findIntersection(const Curve& other_curve);

	virtual point_vec findIntersection(const Spline& other_spline);

	// поиск ближайших точек для двух сплайнов
	radius_vector findClosestPoints(HermitSpline other_spline);

	// найти пересечение сплайна со сплайном
	// TODO подумать о константной ссылке, пока по значению

	point_vec findIntersection(const HermitSpline& other_spline);


};