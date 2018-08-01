#include "common_functions.h"
#include "curve.h"
#include "structs_types.h"
#include "hermit_spline.h"
#include "test_runner.h"
#include "Test_classes.h"




void TestMakeSpline()
{
	// for straight line
	{

	}
	// for ellips
	{

	}
}

void TestMakeInnerGrid()
{
	//straight line
	{
		// base points
		bpoints bp = {
				{0.0, {0.0, 1.0}},
				{1.0, {1.0, 1.0}},
				{2.0, {2.0, 1.0}},
				{3.0, {3.0, 1.0}}
		};
		straightLineCoeffs c_x(1.0, 0.0);
		straightLineCoeffs c_y(0.0, 1.0);
		// Line object
		TestStraightLine line(c_x, c_y, bp);
		// проверить коэффициенты

		bpoints igrid = line.makeInnerGrid();
		AssertEqual(igrid == bp, true, "Test Inner Grid for Straight Line");
	}
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

void TestCommonFW()
{
	AssertEqual(f_w(1, 1, 2), 0, " case 0 ");
	AssertEqual(f_w(1.5, 1, 2), 0.5, " case 0.5 ");
	AssertEqual(f_w(2, 1, 2), 1, " case 1 ");
}

void TestAll()
{
	TestRunner tr;

	//tr.RunTest(TestMakeInnerGrid, "Test inner grid");
	//tr.RunTest(TestFindIntersection, "Test find intersection");
	//tr.RunTest(TestMakeSpline, "Test Make spline");
	//tr.RunTest(TestIterationMethod, "Test Iteration method");
	tr.RunTest(TestCommonFW, "Test Common FW");
}


int main( int argc, char* argv[])
{
	// запускаем юнит-тесты
	TestAll();

	// для функций, заданных параметрически, построим сплайны 
	HermitSpline s1, s2;
	
	std::cout << "Reading base points..." << std::endl;
	s1.readBasePoints(argv[1]);
	s2.readBasePoints(argv[2]);
	
	std::cout << "Creating splines..." << std::endl;
	s1.MakeSpline();
	s2.MakeSpline();	

	std::cout << "Make inner grid..." <<std::endl;
	s1.makeInnerGrid();
	s2.makeInnerGrid();

	// вектор для точек пересечения
	std::vector<point> vec_intersect;
	std::cout << "Finding intersection..." << std::endl;	

	vec_intersect = findCurvesIntersection(s1,s2, 1.0e-9, 10);
	std::cout << "Intersect points number = "<< vec_intersect.size() << std::endl;

	return 0;
}

