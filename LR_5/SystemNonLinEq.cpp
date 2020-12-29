#include "Header.h"

SystemNonLinEq::SystemNonLinEq(std::function<void(double&, double&)> f, double a, double b, std::string fileName)
{
	fun = f;
	streamName = fileName;

	left = a;
	right = b;
}

void SystemNonLinEq::Grid(double h)
{
	int n = 2 * right / h;

	for (int i = 0; i <= n; i++)
		omega.push_back(left + i * h);

	//for (const auto& o : omega)
	//	std::cout << o << " ";
	//std::cout << "\n";
}

bool SystemNonLinEq::Newton()
{
	stream << "Newton's method:\n";

	if (!omega.size())
	{
		std::cout << "No localization segments!\n";
		return false;
	}

	double x, x_k;
	double y, y_k;

	int size = omega.size();
	double leftSide;
	double rightSide;

	std::vector<int> iterations;

	for (int i = 0; i < size; i += 2)
	{
		for (int j = 0; j < size; j++)
		{
			iterations.push_back(0);

			//Начальное приближение
			x = omega[i];
			y = omega[j];

			do
			{
				iterations.back()++;
				if (iterations.back() > 30)
					break;

				x_k = x;
				y_k = y;



				//x = x_k - fun(x_k) / Derivative(x_k);


			} while (fabs(x_k - x) > eps);

			if (iterations.back() > 30)
			{
				roots[0][i] = -100.;
				roots[1][i] = -100.;
				continue;
			}
				
			roots[0][i] = x;
			roots[1][i] = y;
		}
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

	return true;
}

void SystemNonLinEq::StreamOpen()
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

void SystemNonLinEq::StreamClose()
{
	if (stream.is_open())
		stream.close();
}

SystemNonLinEq::~SystemNonLinEq()
{
	if (stream.is_open())
		stream.close();
}