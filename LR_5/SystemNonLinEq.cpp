#include "Header.h"

double SystemNonLinEq::Derivative(std::function<double(double, double)> f, double zn1, double zn2, int dd)
{
	if (dd == 1)
		return (f(zn1 + eps, zn2) - f(zn1, zn2)) / eps;
	else
		return (f(zn1, zn2 + eps) - f(zn1, zn2)) / eps;
}

SystemNonLinEq::SystemNonLinEq(std::function<double(double, double)> f1, std::function<double(double, double)> f2, double a, double b, std::string fileName)
{
	fun1 = f1;
	fun2 = f2;
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
	//stream << "Newton's method:\n";

	if (!omega.size())
	{
		std::cout << "No localization segments!\n";
		return false;
	}

	double x, x_k, x_p, x_pk;
	double y, y_k, y_p, y_pk;

	//double  x_p, x_pk;
	//double  y_p, y_pk;

	double dif;

	int size = omega.size();
	//std::cout << "size: " << size << "\n";
	std::vector<int> iterations;
	std::vector<double> jacobi;

	double maxdbl = 1.e+6;

	int scet = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			scet++;
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

//--------------------------------------------------------------------
				//Вектор поправки (метод простых итераций)
			//	x_pk = fun1(0., 0.);
			//	y_pk = fun2(0., 0.);
			//	do {
			//		
			//		x_p = (-Derivative(fun1, x_pk, y_pk, 1) + 1.)*x_pk - Derivative(fun1, x_pk, y_pk, 2)*y_pk - fun1(x_pk, y_pk);
			//		y_p = -Derivative(fun2, x_pk, y_pk, 1)*x_pk + (-Derivative(fun2, x_pk, y_pk, 2)+1.)*y_pk - fun2(x_pk, y_pk);
			//		
			//		std::cout << "x_p: " << x_p << ", y_p: " << y_p << "\n";

			//		//Норма разницы
			//		if (fabs(x_p - x_pk) > fabs(y_p - y_pk))
			//			dif = fabs(x_p - x_pk);
			//		else
			//			dif = fabs(y_p - y_pk);

			//		if (1.e+6 > x_p || 1.e+6 > y_p)
			//		{
			//			std::cout << "Rasxoditsya\n";
			//			return false;
			//		}

			//		x_pk = x_p;
			//		y_pk = y_p;
			//	} while (dif > eps);


			//	x = x_k + x_p;
			//	y = y_k + y_p;
//--------------------------------------------------------------------
				
				jacobi.push_back(Derivative(fun1, x_k, y_k, 1));
				jacobi.push_back(Derivative(fun1, x_k, y_k, 2));
				jacobi.push_back(Derivative(fun2, x_k, y_k, 1));
				jacobi.push_back(Derivative(fun2, x_k, y_k, 2));

				double det = jacobi[0] * jacobi[3] - jacobi[1] * jacobi[2];
				std::swap(jacobi[0], jacobi[3]);
				jacobi[0] *= 1 / det;
				jacobi[3] *= 1 / det;
				jacobi[1] *= -1 / det;
				jacobi[2] *= -1 / det;

				x = x_k - jacobi[0] * fun1(x_k, y_k) - jacobi[1] * fun2(x_k, y_k);
				y= y_k - jacobi[2] * fun1(x_k, y_k) - jacobi[3] * fun2(x_k, y_k);

				jacobi.clear();

				if (fabs(x - x_k) > fabs(y - y_k))
					dif = fabs(x - x_k);
				else
					dif = fabs(y - y_k);
				//std::cout << "dif " << dif << "\n";

				if (fabs(x) > maxdbl || fabs(y) > maxdbl)
				{
					iterations.back() = 31;
					break;
				}
					
			} while (dif > eps);

			if (iterations.back() > 30 || fabs(x) > maxdbl || fabs(y) > maxdbl)
			{
				rootX.push_back(-100.);
				rootY.push_back(-100.);
				continue;
			}

			rootX.push_back(x);
			rootY.push_back(y);
		}
	}
	std::cout << "scet " << scet;
	std::cout << "its " << iterations.size();
	for (const auto& iter : iterations)
		stream << iter << "\n";

	//for (int i = 0; i < rootX.size(); i++)
	//	std::cout << rootX[i] << " " << rootY[i] << "\n";

	//Вывод для отрисовки
	//std::cout << "Roots:\n";
	//for (int i = 0; i < rootX.size(); i++)
	//	std::cout << rootX[i] << " " << rootY[i] << "\n";

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