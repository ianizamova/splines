#include "hermit_spline.h"
#include "common_functions.h"

// построить эрмитов сплайн
void HermitSpline::MakeSpline() {
	radius_vector rv = GetRVec();

	std::vector<double> p, q;  // p- радиус-вектор, q - производная

	size_t i = 0;
	// p_i
	for (auto r_i : rv)
	{
		p.push_back(r_i.r);
	}
	//q_i
	// просто заполняем нулевой элемент
	q.push_back(0.0);
	size_t n = rv.size() - 1;
	for (size_t i = 1; i < n; ++i)
	{
		double s_i = abs(p[i] - p[i - 1]);
		double s_i_1 = abs(p[i + 1] - p[i]);

		q.push_back((s_i_1*(p[i] - p[i - 1]) + s_i*(p[i + 1] - p[i])) / (s_i + s_i_1));
	}

	q[0] = 2.0*(p[1] - p[0]) - q[1];
	q.push_back(2.0*(p[n] - p[n - 1]) - q[n - 1]);

	// coeff
	for (size_t i = 0; i < n; ++i)
	{
		double a0 = p[i];
		double a1 = q[i];
		double a2 = -3.0*p[i] + 3.0*p[i + 1] - 2.0*q[i] - q[i + 1];
		double a3 = 2.0*p[i] - 2.0*p[i + 1] + q[i] + q[i + 1];

		coeffs_.push_back({ a0, a1,a2,a3 });
	}


};

point_vec HermitSpline::findIntersection(const HermitSpline& other_spline)
{
	point_vec v;

	// проверить пересечение по базовым точкам
	v = findBasePointsIntersection(other_spline);

	// считается, что у всех сплайнов один набор точек по времени
	radius_vector rv1 = GetRVec();
	radius_vector rv2 = other_spline.GetRVec();

	std::vector<hermitSplineCoeffs> coeffsA = GetCoeffs();
	std::vector<hermitSplineCoeffs> coeffsB = other_spline.GetCoeffs();

	std::vector<double> w;
	// цикл по количеству разбиений отрезка по времени
	for (size_t i = 0; i < coeffsA.size() - 1; ++i)
	{
		// на каждом отрезке решаем уравнение для определения точек пересечения (методом итераций)
		// сначала найти коэффициенты сплайнов
		double d = coeffsA[i].a0 - coeffsB[i].a0;
		double c = coeffsA[i].a1 - coeffsB[i].a1;
		double b = coeffsA[i].a2 - coeffsB[i].a2;
		double a = coeffsA[i].a3 - coeffsB[i].a3;

		// заполняем вектор точек пересечения
		// если такие точки нашлись
		w.push_back(f_splineIntersection(a, b, c, d));

		// теперь найти соответствующее время
		if (w[i] < 1 && w[i] > 0)
		{
			double t = rv1[i].t + (rv1[i + 1].t - rv1[i].t)*w[i];

			std::cout << "Intersection point is found" << std::endl;
			std::cout << "t " << i << " = " << t << std::endl;

			std::cout << "a = " << a << std::endl;
			std::cout << "b = " << a << std::endl;
			std::cout << "c = " << a << std::endl;
			std::cout << "d = " << a << std::endl;

			double r_t = a*w[i] * w[i] * w[i] + b*w[i] * w[i] + c*w[i] + d;
			std::cout << "r(t) = " << r_t << std::endl;

		} 



	}

	return v;
};

// поиск ближайших точек для двух сплайнов
radius_vector HermitSpline::findClosestPoints(HermitSpline other_spline)
{
	std::vector<hermitSplineCoeffs> coeffsA = GetCoeffs();
	std::vector<hermitSplineCoeffs> coeffsB = other_spline.GetCoeffs();

	radius_vector rv;

	// 1. находим разницу между коэффицентами
	double a, b, c, d;
	for (size_t i = 0; i < coeffsA.size(); ++i)
	{
		std::vector<double> w_min;
		// TODO написать операторы арифметических действий
		a = coeffsA[i].a0 - coeffsB[i].a0;
		b = coeffsA[i].a1 - coeffsB[i].a1;
		c = coeffsA[i].a2 - coeffsB[i].a2;
		d = coeffsA[i].a3 - coeffsB[i].a3;

		std::vector<double> r = solveQuadraticEq(3 * d, 2 * c, b);

		// коэффициенты производной для решения уравнения
		double a_der = 3 * d;
		double b_der = 2 * c;
		double c_der = b;

		// 2. найти экстремум. Производная равна нулю.
		std::vector<double> roots = solveQuadraticEq(a_der, b_der, c_der);
		// если корни есть, надо проверить, где они лежат. Отрицательные не годятся

		// 3. проверить, минимум ли это. Нам нужен минимум. Если минимум, то ок, расстояние нашлось, добавим его в вектор
		for (auto w_i : roots)
		{
			// найдем значение  производной на эпсилон раньше и позже
			double eps = 1.e-6;
			if ((a_der * (w_i - eps)* (w_i - eps) + b_der*(w_i - eps) + c_der < 0) &&
				(a_der * (w_i + eps)* (w_i + eps) + b_der*(w_i + eps) + c_der > 0) &&
				w_i < 1.0 && w_i > 0)
				// и если это минимум (-/+)
			{
				// в этой точке и посчитаем расстояние между сплайнами
				double r = d*w_i*w_i*w_i + c*w_i*w_i + b*w_i + a;
				double t = GetCurve()[i].t + w_i * (GetCurve()[i + 1].t - GetCurve()[i].t);
				rv.push_back({ t, r });
				std::cout << "\n Closest points: t = " << t << " r = " << r << std::endl;
			}
		}

	}
	return rv;
	// теперь из этого вектора надо найти минимальное значение для расстояния
}

point_vec HermitSpline::findIntersection(const Curve& other_curve)
{
	point_vec v;
	return v;
};

point_vec HermitSpline::findIntersection(const Spline& other_spline)
{
	point_vec v;
	return v;
};
