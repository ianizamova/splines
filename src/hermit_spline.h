#pragma once
#include "spline_base.h"
#include "common_functions.h"

class HermitSpline : public Spline
{
	// коэффициенты эрмитова сплайна
	vec_coeffs_herm coeffs_x_;
	vec_coeffs_herm coeffs_y_;

public:
	HermitSpline() {};
	HermitSpline(const vec_coeffs_herm& coeffs_x, const vec_coeffs_herm& coeffs_y) : coeffs_x_(coeffs_x), coeffs_y_(coeffs_y)
	{};

	HermitSpline(const vec_coeffs_herm& coeffs_x, const vec_coeffs_herm& coeffs_y, const bpoints& points) : 
		coeffs_x_(coeffs_x), coeffs_y_(coeffs_y), Spline(points)
	{};

	vec_coeffs_herm GetCoeffsX() const
	{
		return coeffs_x_;
	};

	vec_coeffs_herm GetCoeffsY() const
	{
		return coeffs_y_;
	};

	// построить эрмитов сплайн
	void MakeSpline() override;

	//маленькая функция для постройки сплайна для одной функции f(t)
	vec_coeffs_herm make_1d_hermit_spline(const f_t& x_t);

	// построение внутренней сетки по заменяющим отрезкам
	//virtual bpoints makeInnerGrid();

	virtual double x_t(double t, size_t i)
	{
		auto coef = coeffs_x_.at(i).second;
		double w = f_w(t, coeffs_x_.at(i).first, coeffs_x_.at(i+1).first);
		return coef.a3_ * w*w*w + coef.a2_*w*w + coef.a1_ *w + coef.a0_;
	};
	virtual double xdt_t(double t, size_t i)
	{
		auto coef = coeffs_x_.at(i).second;
		double w = f_w(t, coeffs_x_.at(i).first, coeffs_x_.at(i + 1).first);
		return 3*coef.a3_*w*w + 2*coef.a2_*w + coef.a1_;
	};
	virtual double xdt2_t(double t, size_t i)
	{
		auto coef = coeffs_x_.at(i).second;
		double w = f_w(t, coeffs_x_.at(i).first, coeffs_x_.at(i + 1).first);
		return 6*coef.a3_ * w + 2*coef.a2_;
	};
	virtual double y_t(double t, size_t i)
	{
		auto coef = coeffs_y_.at(i).second;
		double w = f_w(t, coeffs_x_.at(i).first, coeffs_x_.at(i + 1).first);
		return coef.a3_ * w*w*w + coef.a2_*w*w + coef.a1_ *w + coef.a0_;
	};
	virtual double ydt_t(double t, size_t i)
	{
		auto coef = coeffs_y_.at(i).second;
		double w = f_w(t, coeffs_x_.at(i).first, coeffs_x_.at(i + 1).first);
		return 3 * coef.a3_*w*w + 2 * coef.a2_*w + coef.a1_;
	};
	virtual double ydt2_t(double t, size_t i)
	{
		auto coef = coeffs_y_.at(i).second;
		double w = f_w(t, coeffs_x_.at(i).first, coeffs_x_.at(i + 1).first);
		return 6 * coef.a3_ * w + 2 * coef.a2_;
	};

};