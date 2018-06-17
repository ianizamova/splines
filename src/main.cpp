#include "common_functions.h"
#include "curve.h"
#include "structs_types.h"
#include "hermit_spline.h"


int main( int argc, char* argv[])
{
	// надо считать время
	double t_min, t_max, step;

	// вектор значений временных точек
	std::vector<double> vector_t;
	
	// для функций, заданных параметрически, построим сплайны 
	HermitSpline s1, s2;
	
	std::cout << "Reading base points..." << std::endl;
	s1.readBasePoints(argv[1]);
	s2.readBasePoints(argv[2]);
	
	std::cout << "Creating splines..." << std::endl;
	s1.MakeSpline();
	s2.MakeSpline();

	// вектор для точек пересечения
	point_vec vec_intersect;
	std::cout << "Finding intersection..." << std::endl;
	vec_intersect = s1.findIntersection(s2);
	std::cout << "Intersect points number = "<< vec_intersect.size() << std::endl;

	std::cout << "Finding closest points..." << std::endl;
	radius_vector rv = s1.findClosestPoints(s2);
	std::cout << "Closest points number =  " << rv.size() << std::endl;

	// 
	// и теперь найдём точки пересечения или просто ближайшие точки
//	point_vec foundPoints = s1.findIntersection(s2);

	// или в идеале - делаем функцию не-член и вызываем её от двух объектов класса Curve
	// findIntersection(const Curve& c1, const Curve& c2);

	return 0;
}

