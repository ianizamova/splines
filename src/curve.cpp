#include "curve.h"
#include <set>

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
		base_points_.push_back(std::make_pair( t, point(x,y) ));
				
		x_t_.push_back(std::make_pair( t,x ));
		y_t_.push_back(std::make_pair( t,y ));

		// map
		// TODO constructor
		points_[t].x_ = x;
		points_[t].y_ = y;		
	}

	// почему-то проблемы с первой строчкой, надо её удалять
	// TODO убрать это потом, разобраться

};
// TODO
bpoints Curve::makeInnerGrid()
{
	// по базовым точкам у нас построены коэффициенты для сплайнов
	// и мы можем знать значения функции в каждой точке базовых отрезков
	const double dalfa = 3.1415926 / 15; // угол отклонения касательной от кривой
										 // будем двигаться внутри каждого отрезка между базовыми точками
	std::set<double> t_set;
	bpoints inner_grid;

	for (size_t i = 0; i < GetBasePoints().size() - 1; ++i)
	{
		double dt; // шаги  для кривых х и у
		double t_0 = GetX_t()[i].first; // начало отрезка
		double t1 = t_0; // конец отрезка
		t_set.insert(t_0);

		while (t1 < GetX_t()[i + 1].first)
		{
			double cdt = std::pow(xdt_t(t_0, i), 2.0) + std::pow(ydt_t(t_0, i), 2.0);
			double cxc = xdt_t(t_0, i)*ydt2_t(t_0, i) - ydt_t(t_0, i)*xdt2_t(t_0, i);

			if (cxc > 1.0e-10) dt = dalfa*cdt / cxc;
			else dt = GetX_t()[i + 1].first - t_0;

			t1 = t_0 + dt;
			t_0 = t1;
		}
		t_set.insert(t_0);
	}
	size_t i_inner;
	// пересчитать базовые точки для внутренней сетки
	for (size_t i = 0; i < GetBasePoints().size() - 1; ++i)
	{
		i_inner = 0;
		for (auto it_set = t_set.begin(); it_set != t_set.end(); it_set++)
		{			
			if (*it_set < GetX_t()[i + 1].first && *it_set >= GetX_t()[i].first)
			{
				base_to_inner[i].push_back(i_inner);
				inner_to_base[i_inner] = i;
				double x, y, t;
				t = *it_set;
				x = x_t(i, t);
				y = y_t(i, t);
				inner_grid.push_back(std::make_pair(t, point{ x,y }));
			}
			++i_inner;
		}
	}

	return inner_grid;
};
