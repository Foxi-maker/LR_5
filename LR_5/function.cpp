#include "Header.h"

double testf::fun1(double val)
{
	return (val - 0.1)*(val - 0.22)*(val - 0.55)*(val - 0.7)*(val - 0.75);
}
double testf::fun2(double val)
{
	return sqrt(val + 1) - 1;
}

double testf::fun3(double val)
{
	return 35 * pow(val, 3) - 67 * pow(val, 2) - 3 * val + 3;
}

double testf::fun4(double val)
{
	double R1 = sin((pow(val, 4) + pow(val, 3) - 3 * val + 3 - pow(30, 1. / 3)) / 2);
	double R2 = tanh((4 * sqrt(3)*pow(val, 3) - 2 * val - 6 * sqrt(2) + 1) / (-2 * sqrt(3)*pow(val, 3) + val + 3 * sqrt(2)));
	return R1 + R2 + 1.2;
}

double testf::fun5(double val)
{
	return pow(val,4)-1;
}

double testf::system::fun1(double val1, double val2)
{
	return pow(val1, 2) - pow(val2, 2) - 15.;
}

double testf::system::fun2(double val1, double val2)
{
	return val1 * val2 + 4;
}

void testf::system1(double& val1, double& val2)
{
	double temp1 = val1;
	double temp2 = val2;
	val1 = pow(temp1, 2) - pow(temp2, 2) - 15.;
	val2 = temp1 * temp2 + 4;
}

void testf::system2(double& val1, double& val2)
{
	double temp1 = val1;
	double temp2 = val2;
	val1 = pow(temp1, 2) + pow(temp2, 2) + temp1 + temp2 - 8.;
	val2 = pow(temp1, 2) + pow(temp2, 2) + temp1 * temp2 - 7.;
}

void testf::system3(double& val1, double& val2)
{
	double temp1 = val1;
	double temp2 = sqrt(val2);
	val1 = sqrt(temp1) * (sqrt(temp1 + 10.) + temp2) - 100.*temp2;
	val2 = sqrt(temp1) + temp2 - 10.;
}