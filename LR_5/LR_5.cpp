#include "Header.h"

std::fstream NonLinEq::stream;
std::fstream SystemNonLinEq::stream;

int main()
{
	std::vector<NonLinEq> equation;
	//equation.emplace_back(testf::fun1, 0., 1., std::string("fun1"));
	//equation.emplace_back(testf::fun2, -1., 10., std::string("fun2"));
	//equation.emplace_back(testf::fun3, 0., 1., std::string("fun3"));
	//equation.emplace_back(testf::fun4, testf::dfun4, 0., 1., std::string("fun4"));
	
	//std::cout << testf::dfun4(1.) << "\n";

	//for (auto& e : equation)
	//{
	//	e.StreamOpen();

	//	e.LocalizationRoots();
	//	e.Bisection();

	//	e.LocalizationRoots();
	//	e.Newton();

	//	e.StreamClose();
	//}

	std::vector<SystemNonLinEq> systemEquations;
	//systemEquations.emplace_back(testf::system11, testf::system12, -10., 10., std::string("system1"));
	//systemEquations.emplace_back(testf::system2, -10., 10., std::string("system2"));
	systemEquations.emplace_back(testf::system31, testf::system32, 0, 90., std::string("system3"));


	for (auto& s : systemEquations)
	{
		s.StreamOpen();

		s.Grid(4);
		s.Newton();

		s.StreamClose();

	}
}

