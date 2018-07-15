#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include "structs_types.h"

// классы. самый базовый класс - кривая. Просто параметрически заданная линия, у неё есть базовые точки и  радиус-вектор r(t)
class Curve
{
	
	x_y_t points_;  // map
	bpoints base_points_; // vector
	bpoints inner_grid_;

	f_t x_t_, y_t_; //  отдельные х(t), y(t)
	f_t s_t_; // расстояния между точками в (х,у)
	std::map<size_t, std::vector<size_t>> base_to_inner;
	std::map<size_t, size_t> inner_to_base;
public:

	Curve() {};
	Curve(const bpoints& points): base_points_(points)
	{
		inner_grid_ = makeInnerGrid();
	};

	//map
	x_y_t GetPoints() const
	{
		return points_;
	};

	bpoints GetBasePoints() const 
	{
		return base_points_;
	}

	bpoints GetInnerGrid() const
	{
		return inner_grid_;
	};

	f_t GetX_t() const
	{
		return x_t_;
	}
	f_t GetY_t() const
	{
		return y_t_;
	}

	f_t GetS_t()
	{
		return s_t_;
	}

	size_t getBaseI(size_t innerI) const
	{
		return inner_to_base.at(innerI);
	};

	std::vector<size_t> getInnerI(size_t baseI) const 
	{
		return base_to_inner.at(baseI);
	};

	// посчитать расстояния между точками базовыми
	void calcS_t()
	{
		for (size_t i = 0; i < base_points_.size() -1 ; ++i)
		{
			s_t_[i].first = base_points_[i].first;
			double dx = base_points_[i + 1].second.x_ - base_points_[i].second.x_;
			double dy = base_points_[i + 1].second.y_ - base_points_[i].second.y_;
			s_t_[i].second = std::sqrt(dx*dx + dy*dy);
		}
	}

	// чтение базовых точек из файла, построение кривой
	void readBasePoints(const std::string& filename);

	// построением сетки заменяющих отрезков
	virtual bpoints makeInnerGrid();

	// функции, описывающие параметрические уравнения кривой, и их производные
	virtual double x_t(double t, size_t i) const
	{
		return t; 
	};
	virtual double xdt_t(double t, size_t i) const
	{
		return 1;
	};
	virtual double xdt2_t(double t, size_t i)  const
	{
		return 0;
	};
	virtual double y_t(double t, size_t i)  const
	{
		return t;
	};
	virtual double ydt_t(double t, size_t i)  const
	{
		return 1;
	};
	virtual double ydt2_t(double t, size_t i)  const
	{
		return 0;
	};

};



