#pragma once

class SystemNonLinEq
{
	std::function<double(double, double)> fun1;
	std::function<double(double, double)> fun2;
	std::vector<double> omega;									//сетка поиска корней
	//std::vector<double> omega2;
	std::vector<double> rootX;						//массив корней
	std::vector<double> rootY;

	double left, right;

	static std::fstream stream;
	std::string streamName;

	double Derivative(std::function<double(double, double)>,double,double,int);
public:
	SystemNonLinEq(std::function<double(double, double)>, std::function<double(double, double)>, double, double, std::string);

	void Grid(double);

	bool Newton();

	void StreamOpen();
	void StreamClose();

	~SystemNonLinEq();
};

