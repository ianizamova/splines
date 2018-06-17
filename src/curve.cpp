#include "curve.h"

// чтение базовых точек из файла, построение кривой
void Curve::readBasePoints(const std::string& filename)
{
	std::ifstream input(filename);

	//std::cout << "\n\n FILE: " << filename << std::endl;
	double t, x, y, r;
	t = 0; x = 0; y = 0; r = 0;

	std::string str;
	while (std::getline(input, str))
	{
		std::stringstream inp_str(str);

		inp_str >> t >> x >> y;
		//std::cout << "read: t = " << t << " x=" << x << " y=" << y << std::endl;
		curve.push_back({ t,x,y });
		// map
		points_[t].x = x;
		points_[t].y = y;

		r = std::sqrt(x*x + y*y);
		//vector
		r_vec.push_back({ t, r });
		//map
		rv_t_[t] = r;
		//std::cout << "pushed: t = " << t << " r=" << r << std::endl;

	}

	// почему-то проблемы с первой строчкой, надо её удалять
	// TODO убрать это потом, разобраться
	curve.erase(curve.begin());
	r_vec.erase(r_vec.begin());

};

point_vec Curve::findBasePointsIntersection(const Curve& other_curve)
{
	point_vec v;
	for (auto t1_i : curve)
	{
		for (const auto& t2_i : other_curve.GetCurve())
			if (t1_i.t == t2_i.t)
			{
				if (t1_i.x == t2_i.x && t1_i.y == t2_i.y)
					// и если есть, то добавить такие точки в вектор
					v.push_back(std::make_pair(t1_i.x, t1_i.y));
			}
	}
	return v;
}

point_vec Curve::findIntersection(const Curve& other_curve)
{
	point_vec v;
	//1. проверить, есть ли пересечение по базовым точкам
	v = findBasePointsIntersection(other_curve);

	// 2. проверять пересечение уже по другим точкам

	return v;
};