#include "Header.h"

std::fstream NonLinEq::stream;

int main()
{
	std::vector<NonLinEq> elements;
	//elements.emplace_back(testf::fun1, 0., 1., std::string("fun1"));
	//elements.emplace_back(testf::fun2, -1., 10., std::string("fun2"));
	//elements.emplace_back(testf::fun3, 0., 1., std::string("fun3"));
	elements.emplace_back(testf::fun4, 0., 1., std::string("fun4"));

	for (auto& e : elements)
	{
		e.StreamOpen();
		e.LocalizationRoots();

		e.StreamClose();
	}
	
}

