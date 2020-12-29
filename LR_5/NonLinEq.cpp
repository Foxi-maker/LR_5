#include "Header.h"

double NonLinEq::Derivative(double value)
{
	return (fun(value+eps)-fun(value))/eps;
}

NonLinEq::NonLinEq(std::function<double(double)> f, std::function<double(double)>df, double a, double b, std::string fileName)
{
	fun = f;
	dfun = df;
	streamName = fileName;

	left = a;
	right = b;
}

void NonLinEq::LocalizationRoots()
{
	std::cout << streamName << "\n";

	//равномерное разбиение 
	double h = 0.05;

	for (double x = left; x < right; x += h)
	{
		double temp = x + h;

		if (fun(x)*fun(temp) <= DBL_EPSILON)
		{
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
	stream << "Localization:\n";
	for (const auto& l : local)
		stream << l << "\n";
}

bool NonLinEq::Bisection()
{
	stream << "Bisection method:\n";

	if (!local.size())
	{
		std::cout << "No localization segments!\n";
		std::cout << "Roots:\n";
		for (const auto& r : roots)
		{
			std::cout << r << " ";
		}
		std::cout << "\n";
		return false;
	}

	int size = local.size();
	double leftSide;
	double rightSide;
	double middle;

	std::vector<int> iterations;
	int indexRoot = 1;
	for (int i = 0; i < size; i += 2)
	{
		iterations.push_back(0);
		stream << "Root " << indexRoot << "\n";
		indexRoot++;
		leftSide = local[i];
		rightSide = local[i + 1];
		while ((rightSide - leftSide) > 2 * eps)
		{
			iterations.back()++;

			middle = leftSide + (rightSide - leftSide) / 2;
			if (fun(middle)*fun(rightSide) <= DBL_EPSILON)
				leftSide = middle;
			else
				rightSide = middle;
			stream << middle << "\n";
		}
		roots.push_back(middle);
	}

	stream << "Iterations:\n";
	for (const auto& iter : iterations)
	{
		stream << iter << " ";
	}
	stream << "\n";


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
	stream << "\n";

	local.clear();
	roots.clear();
	return true;
}

bool NonLinEq::Newton()
{
	stream <<"Newton's method:\n";

	if (!local.size())
	{
		//std::cout << "No localization segments!\n";
		std::cout << "Roots:\n";
		for (const auto& r : roots)
		{
			std::cout << r << " ";
		}
		std::cout << "\n";
		return false;
	}

	double x,x_k;

	int size = local.size();
	double leftSide;
	double rightSide;

	std::vector<int> iterations;
	int indexRoot = 1;
	for (int i = 0; i < size; i += 2)
	{
		iterations.push_back(0);

		stream << "Root " << indexRoot << "\n";
		indexRoot++;

		leftSide = local[i];
		rightSide = local[i + 1];

		//Ќачальное приближение
		x = (rightSide*fun(leftSide) - leftSide * fun(rightSide)) / (fun(leftSide) - fun(rightSide));

		do
		{
			iterations.back()++;

			x_k = x;
			//TODO: D
			x = x_k - fun(x_k) / dfun(x_k);

			//ѕроверка на выход из отрезка локализации
			if (x<leftSide || x>rightSide)
			{
				std::cout << "x: " << x << "\n";
				//»тераци€ по методу хорд
				if (fun(x_k)*fun(rightSide) < 0)
					x = x_k - (fun(x_k)*(x_k - rightSide)) / (fun(x_k) - fun(rightSide));
				else
					x = x_k - (fun(x_k)*(x_k - leftSide)) / (fun(x_k) - fun(leftSide));
			}
			stream << x << "\n";
		} while (fabs(x_k - x) > eps);

		roots.push_back(x);
	}

	stream << "Iterations:\n";
	for (const auto& iter : iterations)
	{
		stream << iter << " ";
	}
	stream << "\n";

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
	stream << "\n";

	local.clear();
	roots.clear();

	return true;
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