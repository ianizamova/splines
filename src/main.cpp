#include "common_functions.h"
#include "curve.h"
#include "structs_types.h"
#include "hermit_spline.h"
#include "test_runner.h"



void TestQuadraticEq()
{
	// 0 roots
	AssertEqual(solveQuadraticEq(1, 1, 1).size(), 0, " 0 roots ");
	// 1 root
	AssertEqual(solveQuadraticEq(1, 2, 1).size(), 1, " 1 root ");
	// 2 roots
	AssertEqual(solveQuadraticEq(1, 3, 1).size(), 2, " 2 roots ");
}

void TestMakeSpline()
{
	// for direct line
	// for parabolic line
	// for cubic line
	// for circle

}

void TestFindIntersection()
{
	// parallel lines
	// orthogonal lines
	// two points
	// periodical function
}

void TestIterationMethod()
{
}

void TestAll()
{
	TestRunner tr;

	tr.RunTest(TestQuadraticEq, "Test Quadratic equation");
	tr.RunTest(TestFindIntersection, "Test find intersection");
	tr.RunTest(TestMakeSpline, "Test Make spline");
	tr.RunTest(TestIterationMethod, "Test Iteration method");
}


int main( int argc, char* argv[])
{
	TestAll();
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
	std::vector<point> vec_intersect;
	std::cout << "Finding intersection..." << std::endl;

	vec_intersect = findCurvesIntersection(s1,s2, 1.0e-9);
	std::cout << "Intersect points number = "<< vec_intersect.size() << std::endl;

	std::cout << "Finding closest points..." << std::endl;
	
//	std::cout << "Closest points number =  " << rv.size() << std::endl;

	// 
	// и теперь найдём точки пересечения или просто ближайшие точки
	//	point_vec foundPoints = s1.findIntersection(s2);

	// или в идеале - делаем функцию не-член и вызываем её от двух объектов класса Curve
	// findIntersection(const Curve& c1, const Curve& c2);

	return 0;
}

