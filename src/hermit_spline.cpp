#include "hermit_spline.h"
#include "structs_types.h"
#include "common_functions.h"

#include <utility>
#include <set>

double HermitSpline::x_t(double t, size_t i) const
{
	//std::cout << "In hermit spline function x(t)" <<std::endl;

	auto coef = coeffs_x_.at(i).second;
	double w = f_w(t, x_t_.at(i).first, x_t_.at(i+1).first);
	return coef.a3_ * w*w*w + coef.a2_*w*w + coef.a1_ *w + coef.a0_;
};
double HermitSpline::xdt_t(double t, size_t i) const
{
	auto coef = coeffs_x_.at(i).second;
	double w = f_w(t, x_t_.at(i).first, x_t_.at(i + 1).first);
	return 3*coef.a3_*w*w + 2*coef.a2_*w + coef.a1_;
};
double HermitSpline::xdt2_t(double t, size_t i) const
{
	auto coef = coeffs_x_.at(i).second;
	double w = f_w(t, x_t_.at(i).first, x_t_.at(i + 1).first);
	return 6*coef.a3_ * w + 2*coef.a2_;
};
double HermitSpline::y_t(double t, size_t i) const
{
	auto coef = coeffs_y_.at(i).second;
	double w = f_w(t, y_t_.at(i).first, y_t_.at(i + 1).first);
	return coef.a3_ * w*w*w + coef.a2_*w*w + coef.a1_ *w + coef.a0_;
};
double HermitSpline::ydt_t(double t, size_t i) const
{
	auto coef = coeffs_y_.at(i).second;
	double w = f_w(t, y_t_.at(i).first, y_t_.at(i + 1).first);
	return 3 * coef.a3_*w*w + 2 * coef.a2_*w + coef.a1_;
};
double HermitSpline::ydt2_t(double t, size_t i) const
{
	auto coef = coeffs_y_.at(i).second;
	double w = f_w(t, y_t_.at(i).first, y_t_.at(i + 1).first);
	return 6 * coef.a3_ * w + 2 * coef.a2_;
};

//маленькая функция для постройки одномерного сплайна для одной функции
vec_coeffs_herm HermitSpline::make_1d_hermit_spline(const f_t& x_t)
{
	vec_coeffs_herm vec_res;
	std::vector<double> p, q, s, t;
	for (auto item : x_t)
	{
		t.push_back(item.first);
		p.push_back(item.second);		
	}
	f_t s1 = GetS_t();
	for (auto item : s1)
	{
		s.push_back(item.second);
	}
	// зададим размер вектора
	q.reserve(p.size()-1);
	//заполним нулевой элемент
	q.push_back(0.0); 
	// чтобы посчитать q, надо сначала посчитать s
	size_t num_scheme = 0u;
	for (size_t i = 1; i < p.size()-1; ++i)
	{
		//std::cout << "make_1d_hermit_spline 4 for 1" << std::endl;
		switch (num_scheme)
		{
		//std::cout << "make_1d_hermit_spline 4 switch" << std::endl;
			// простая схема
			case 0u:
			{
				q.insert(std::next(q.begin(),i),(p[i + 1] - p[i-1]) / (t[i+1] - t[i-1]));
			}	break;
			// схема номер 2 с расстояниями между точками
			// тут надо уменьшить размер контейнера
			case 1u:
			{
				q.insert(std::next(q.begin(),i),(s[i + 1] * (p[i] - p[i - 1]) + s[i] * (p[i + 1] - p[i]))); // s[i + 1] * (p[i] - p[i - 1]) + s[i] * (p[i + 1] - p[i]);
				q[i] /= (s[i + 1] + s[i]);
			}	break;
			// схема номер 3 с расстояниями между точками
			case 2u: 
			{
				q.insert(std::next(q.begin(), i),(s[i] * (p[i] - p[i - 1]) + s[i+1] * (p[i + 1] - p[i])));
				q[i] /= (s[i + 1] + s[i]);
			}	break;
		}
	}
	// производная на концах
	q.insert(q.begin(), (2 * (p[1] - p[0]) - q[1]));
	q.erase(next(q.begin()));
	q.insert(prev(q.end()), (2 * (p[p.size() - 1] - p[p.size() - 2]) - q[p.size() - 2]));

	for (size_t i = 0; i < p.size()-1 ; ++i)
	{
		double a0 = p[i];
		double a1 = q[i];
		double a2 = -3 * p[i] + 3 * p[i + 1] - 2 * q[i] - 2 * q[i + 1];
		double a3 = 2 * p[i] - 2 * p[i + 1] + q[i] + q[i + 1];
		vec_res.push_back(std::make_pair(t[i], hermitSplineCoeffs(a0,a1,a2,a3)));
	}

	return vec_res;

}
// построить эрмитов сплайн
void HermitSpline::MakeSpline() {
//	std::vector<double> p, q;  // p- радиус-вектор, q - производная
	//vec_coeffs_herm coeffs_x, coeffs_y;
	// для х и для у построим сплайны эрмита
	coeffs_x_ = make_1d_hermit_spline(x_t_);
	coeffs_y_ = make_1d_hermit_spline(y_t_);

};
