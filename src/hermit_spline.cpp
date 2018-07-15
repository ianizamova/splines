#include "hermit_spline.h"
#include "structs_types.h"
#include "common_functions.h"

#include <utility>
#include <set>

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
	// расстояния между точками
	f_t s1 = GetS_t();
	for (auto item : s1)
	{
		s.push_back(item.second);
	}

	// зададим размер вектора
	q.reserve(p.size());
	//заполним нулевой элемент
	q.push_back(0.0); 

	// чтобы посчитать q, надо сначала посчитать s
	size_t num_scheme = 0u;
	for (size_t i = 1; i < p.size()-1; ++i)
	{
		switch (num_scheme)
		{
			// простая схема
			case 0u:
			{
				q.insert(next(q.begin(),i),(p[i + 1] - p[i-1]) / (t[i+1] - t[i-1]));
			}	break;
			// схема номер 2 с расстояниями между точками
			// тут надо уменьшить размер контейнера
			case 1u:
			{
				q[i + 1] = s[i + 1] * (p[i] - p[i - 1]) + s[i] * (p[i + 1] - p[i]);
				q[i + 1] /= (s[i + 1] + s[i]);
			}	break;
			// схема номер 3 с расстояниями между точками
			case 2u: 
			{
				q[i + 1] = s[i] * (p[i] - p[i - 1]) + s[i+1] * (p[i + 1] - p[i]);
				q[i + 1] /= (s[i + 1] + s[i]);
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
	vec_coeffs_herm coeffs_x, coeffs_y;
	// для х и для у построим сплайны эрмита
	coeffs_x = make_1d_hermit_spline(GetX_t());
	coeffs_y = make_1d_hermit_spline(GetY_t());

};
