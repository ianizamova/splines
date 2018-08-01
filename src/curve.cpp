#include "curve.h"
#include <numeric>
#include <limits>
#include <set>


template< class T >
void print_set (const std::set<T>& s)
{
	std::cout << "[ ";
	for(auto i: s)
	{
		std::cout << i << " ";
	}
	std::cout << "]"<< std::endl;
}

Curve::Curve(const bpoints& points)
{
	base_points_ = points;
	//std::cout << "Curve is constructed!!! " << std:: endl;
	for (auto item: points)
	{
		//std::cout << "x= " << item.second.x_ << ", y= "<< item.second.y_ <<std::endl;
		x_t_.push_back(std::make_pair(item.first, item.second.x_));
		y_t_.push_back(std::make_pair(item.first, item.second.y_));
	}
};
// посчитать расстояния между точками базовыми
void Curve::calcS_t()
{
	s_t_.reserve(base_points_.size() -1u);
	for (size_t i = 0; i < base_points_.size() -1 ; ++i)
	{

		double dx = base_points_[i + 1].second.x_ - base_points_[i].second.x_;
		double dy = base_points_[i + 1].second.y_ - base_points_[i].second.y_;
		double ds = std::sqrt(dx*dx + dy*dy);
		s_t_.push_back(std::make_pair(base_points_.at(i).first, ds));
	}
	//std::cout << "s_t size: "<< s_t_.size() << std::endl;
}
// чтение базовых точек из файла, построение кривой
void Curve::readBasePoints(const std::string& filename)
{
	std::ifstream input;
	input.open(filename.c_str());
	if(input.is_open())
	{
		std::cout << "\n\n FILE: " << filename << " is read "<< std::endl;
		double t, x, y, r;
		t = 0; x = 0; y = 0; r = 0;

		base_points_.clear();

		std::string str;
		std::size_t i = 0;
		while (std::getline(input, str))
		{
			std::stringstream inp_str(str);

			inp_str >> t >> x >> y;
			base_points_.push_back(std::make_pair( t, point(x,y) ));

			x_t_.push_back(std::make_pair( t,x ));
			y_t_.push_back(std::make_pair( t,y ));
		}

		std::cout << "base grid is constructed" << std::endl;
		//std::cout << "size: "<< x_t_.size() << std::endl;

		calcS_t(); // расчет расстояний между точками

	}
	else
	{
		std::cout << "file not found =("<< std::endl;
	}

};

bpoints Curve::makeInnerGrid()
{
	// по базовым точкам у нас построены коэффициенты для сплайнов
	// и мы можем знать значения функции в каждой точке базовых отрезков
	const double dalfa = M_PI / 10; // угол отклонения касательной от кривой
									// будем двигаться внутри каждого отрезка между базовыми точками
	std::set<double> t_set;
	bpoints inner_grid;
	std::map<size_t, std::vector<size_t>> btoi;
	std::map<size_t, size_t> itob;
	std::size_t i0 = 0;
	std::size_t i00 = 0;
	for (size_t i = 0; i < GetBasePoints().size() - 1; ++i)
	{
		double dt; // шаги  для кривых х и у
		double t_0 = GetX_t()[i].first; // начало отрезка

		double t1 = t_0; // конец отрезка
		t_set.insert(t_0);
		double t_upper_limit = GetX_t()[i + 1].first;
		t_set.insert(t_upper_limit);

		while (t1 < t_upper_limit)
		{
			double cdt = std::pow(xdt_t(t_0, i), 2.0) + std::pow(ydt_t(t_0, i), 2.0);
			double cxc = xdt_t(t_0, i)*ydt2_t(t_0, i) - ydt_t(t_0, i)*xdt2_t(t_0, i);
			if (std::abs(cxc) > std::numeric_limits<double>::min()) dt = dalfa*cdt / cxc;
			else
				{
					//std::cout << "oops" << std::endl;
				    dt = t_upper_limit - t_0;
				   // t1 = t_upper_limit;
				    t_set.insert(t_upper_limit);
				}
	//		std::cout<< "dt : " << dt << std:: endl;

			t1 = t_0 + dt;
			//std::cout<< "t1 : " << t1 << std:: endl;
			if(t1 <= t_upper_limit) {
				t_set.insert(t1);
			}
			else
			{
				t1 = t_upper_limit;
				t_set.insert(t1);
			}
			t_0 = t1;
			t_set.insert(t1);

		}
		t_set.insert(t_0);

	}
	size_t i_inner;

	// пересчитать базовые точки для внутренней сетки
	for (size_t i = 0; i < GetBasePoints().size() - 1; ++i)
	{
		std::size_t last = GetBasePoints().size() - 1;
		i_inner = 0;
		for (auto it_set = t_set.begin(); it_set != t_set.end(); it_set++)
		{
			if (*it_set < GetX_t().at(i+1).first && *it_set >= GetX_t().at(i).first)
			{
				btoi[i].push_back(i_inner);
				itob[i_inner] = i;

				double x, y, t;
				t = *it_set;
				x = x_t(t, i);
				y = y_t(t, i);
				inner_grid.push_back(std::make_pair(t, point{ x,y }));
			}
			else if(*it_set == last)
			{
				btoi[last].push_back(i_inner);
				itob[i_inner] = last;
				double x, y, t;
				t = *it_set;
				x = x_t(t, last);
				y = y_t(t, last);
				inner_grid.push_back(std::make_pair(t, point{ x,y }));
			}
			++i_inner;

		}
	}

	SetInnerGrid(inner_grid, btoi, itob);
	return inner_grid;
};
