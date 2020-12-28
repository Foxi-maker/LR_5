#include "Header.h"

NonLinEq::NonLinEq(std::function<double(double)> f, double a, double b, std::string fileName)
{
	fun = f;
	streamName = fileName;

	left = a;
	right = b;
}

void NonLinEq::LocalizationRoots()
{
	std::cout << streamName << "\n";
	//равномерное разбиение 
	double h = 0.05;
	//double end = b - 0.04;
	for (double x = left; x < right; x += h)
	{
		double temp = x + h;
		//std::cout << "x: " << x << "\n";
		//std::cout << "fun(x): " << fun(x) << "\n";
		//std::cout << "temp: " << temp << "\n";

		if (fun(x)*fun(temp) <= DBL_EPSILON)
		{
			//std::cout << "x: " << x << "\n";
			//std::cout << "fun(x): "<<fun(x)<<"\n";
			//std::cout << "temp: " << temp << "\n";
			//std::cout << "fun(temp): " << fun(temp) << "\n";
			if (fabs(fun(x)) < DBL_EPSILON)
			{
				roots.push_back(x);
				continue;
			}
			if (fabs(fun(temp)) < DBL_EPSILON)
			{
				roots.push_back(temp);
				x += h;
				continue;
			}
			local.push_back(x);
			local.push_back(temp);
		}
	}

	//stream << "Localization:\n";
	//int i = 1;
	//for (const auto& l : local)
	//{
	//	stream << l << " ";
	//	if (i % 2 == 0)
	//		stream << "\n";
	//	i++;
	//}

	//stream << "Roots:\n";
	//for (const auto& r : roots)
	//{
	//	stream << r << " ";
	//}

	//std::cout << "Localization:\n";
	//i = 1;
	//for (const auto& l : local)
	//{
	//	std::cout << l << " ";
	//	if (i % 2 == 0)
	//		std::cout << "\n";
	//	i++;
	//}

	//std::cout << "Roots:\n";
	//for (const auto& r : roots)
	//{
	//	std::cout << r << " ";
	//}
	//std::cout << "\n";
}

bool NonLinEq::Bisection()
{
	if (!local.size())
	{
		std::cout << "Ќет отрезков локализации!\n";
		return 1;
	}

	int size = local.size();
	double leftSide;
	double rightSide;
	double middle;

	for (int i = 0; i < size; i += 2)
	{
		leftSide = local[i];
		rightSide = local[i + 1];
		while ((rightSide - leftSide) > 2 * eps)
		{
			middle = leftSide + (rightSide - leftSide) / 2;
			if (fun(middle)*fun(rightSide) <= DBL_EPSILON)
				leftSide = middle;
			else
				rightSide = middle;
		}
		roots.push_back(middle);
	}

	std::cout << "Roots:\n";
	for (const auto& r : roots)
	{
		std::cout << r << " ";
	}
	std::cout << "\n";

	stream << "Roots:\n";
	for (const auto& r : roots)
	{
		stream << r << " ";
	}
}

void NonLinEq::StreamOpen()
{
	if (stream.is_open())
		stream.close();
	stream.open("Results\\" + streamName + ".txt", std::ios_base::out);
	if (!stream.is_open())
	{
		std::cout << "File " << streamName << " was not opened for writing!";
		exit(1);
	}

}

void NonLinEq::StreamClose()
{
	if (stream.is_open())
		stream.close();
}

NonLinEq::~NonLinEq()
{
	if (stream.is_open())
		stream.close();
}