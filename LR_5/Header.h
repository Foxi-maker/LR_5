#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <string>

#include "NonLinEq.h"
#include "SystemNonLinEq.h"

const double eps = 1.e-6;

namespace testf
{
	struct system
	{
		double fun1(double, double);
		double fun2(double, double);
	};
	//нелинейные уравнения
	double fun1(double);
	double fun2(double);
	double fun3(double);
	double fun4(double);
	double fun5(double);

	//системы нелинейных уравнений
	void system1(double&, double&);
	void system2(double&, double&);
	void system3(double&, double&);
}