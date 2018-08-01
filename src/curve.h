#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <utility>
#include "structs_types.h"

// классы. самый базовый класс - кривая. Просто параметрически заданная линия, у неё есть базовые точки и  радиус-вектор r(t)
class Curve
{
public:
	//x_y_t points_;  // map
	bpoints base_points_; // vector
	bpoints inner_grid_;

	f_t x_t_, y_t_; //  отдельные х(t), y(t)
	f_t s_t_; // расстояния между точками в (х,у)
	std::map<size_t, std::vector<size_t>> base_to_inner;
	std::map<size_t, size_t> inner_to_base;
public:


	Curve() {
		base_points_ = { {0.0, point(0.0, 0.0)} };
		inner_grid_ = { { 0.0, point(0.0, 0.0) } };
		//std::cout << "Curve is constructed!!! " << std:: endl;
	};
	Curve(const bpoints& points);
//	{
//		std::cout << "Curve is constructed!!! " << std:: endl;
//		for (auto item: points)
//		{
//			std::cout << "x= " << item.second.x_ << ", y= "<< item.second.y_ <<std::endl;
//			x_t_.push_back(std::make_pair(item.first, item.second.x_));
//			y_t_.push_back(std::make_pair(item.first, item.second.y_));
//		}
//	};

	bpoints GetBasePoints() const 
	{
		return base_points_;
	}

	bpoints GetInnerGrid() const
	{
		return inner_grid_;
	};

	void SetInnerGrid(const bpoints& inner_grid, const std::map<size_t, std::vector<size_t>>& btoi, const std::map<size_t, size_t>& itob)
	{
		inner_grid_ = inner_grid;
		base_to_inner = btoi;
		inner_to_base = itob;
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
	void calcS_t();


	// чтение базовых точек из файла, построение кривой
	void readBasePoints(const std::string& filename);

	// построением сетки заменяющих отрезков
	bpoints makeInnerGrid();

	// функции, описывающие параметрические уравнения кривой, и их производные
	virtual double x_t(double t, size_t i) const =0;
	virtual double xdt_t(double t, size_t i) const = 0; 
	virtual double xdt2_t(double t, size_t i)  const = 0;
	virtual double y_t(double t, size_t i)  const = 0;
	virtual double ydt_t(double t, size_t i)  const = 0;
	virtual double ydt2_t(double t, size_t i)  const = 0;

};



