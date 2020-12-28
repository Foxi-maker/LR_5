#include "Header.h"

double testf::fun1(double x)
{
	return (x - 0.1)*(x-0.22)*(x-0.55)*(x-0.7)*(x-0.75);
}
double testf::fun2(double x)
{
	return sqrt(x+1)-1;
}

double testf::fun3(double x)
{
	return 35*pow(x,3)-67*pow(x,2)-3*x+3;
}

double testf::fun4(double x)
{
	double R1 = sin((pow(x,4)+pow(x,3)-3*x+3-pow(30,1./3))/2);
	double R2 = tanh((4*sqrt(3)*pow(x,3)-2*x-6*sqrt(2)+1)/(-2*sqrt(3)*pow(x,3)+x+3*sqrt(2)));
	return R1+R2+1.2;
}
