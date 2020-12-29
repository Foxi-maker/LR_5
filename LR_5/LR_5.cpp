#include "Header.h"

std::fstream NonLinEq::stream;
std::fstream SystemNonLinEq::stream;

int main()
{
	//std::vector<NonLinEq> equation;
	//equation.emplace_back(testf::fun1, 0., 1., std::string("fun1"));
	//equation.emplace_back(testf::fun2, -1., 10., std::string("fun2"));
	//equation.emplace_back(testf::fun3, 0., 1., std::string("fun3"));
	//equation.emplace_back(testf::fun4, 0., 1., std::string("fun4"));
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
	systemEquations.emplace_back(testf::system1, -10., 10., std::string("system1"));
	//systemEquations.emplace_back(testf::system2, -10., 10., std::string("system2"));
	//systemEquations.emplace_back(testf::system3, -100., 100., std::string("system3"));

	std::vector<SystemNonLinEq> systemEquations;


	for (auto& s : systemEquations)
	{
		s.StreamOpen();

		s.Grid(0.5);
		s.Newton();

		s.StreamClose();

	}

	
}

