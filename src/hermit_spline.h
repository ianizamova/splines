#pragma once
#include "common_functions.h"

class HermitSpline : public Curve
{
	// коэффициенты эрмитова сплайна
	vec_coeffs_herm coeffs_x_;
	vec_coeffs_herm coeffs_y_;

public:
	HermitSpline() {};
	HermitSpline(const vec_coeffs_herm& coeffs_x, const vec_coeffs_herm& coeffs_y) : coeffs_x_(coeffs_x), coeffs_y_(coeffs_y)
	{	};

	HermitSpline(const vec_coeffs_herm& coeffs_x, const vec_coeffs_herm& coeffs_y, const bpoints& points) : 
		coeffs_x_(coeffs_x), coeffs_y_(coeffs_y), Curve(points)
	{	};

	vec_coeffs_herm GetCoeffsX() const
	{
		return coeffs_x_;
	};

	vec_coeffs_herm GetCoeffsY() const
	{
		return coeffs_y_;
	};

	// построить эрмитов сплайн
	void MakeSpline();

	//маленькая функция для постройки сплайна для одной функции f(t)
	vec_coeffs_herm make_1d_hermit_spline(const f_t& x_t);

	// построение внутренней сетки по заменяющим отрезкам
	// bpoints makeInnerGrid();

	virtual double x_t(double t, size_t i) const override;
	virtual double xdt_t(double t, size_t i) const override;
	virtual double xdt2_t(double t, size_t i) const override;
	virtual double y_t(double t, size_t i) const override;
	virtual double ydt_t(double t, size_t i) const override;
	virtual double ydt2_t(double t, size_t i) const override ;


};
