#pragma once

class SystemNonLinEq
{
	std::function<void(double&,double&)> fun;
	std::vector<double> omega;						//����� ������ ������
	//std::vector<double> omega2;
	std::vector<std::vector<double>> roots;						//������ ������

	double left, right;

	static std::fstream stream;
	std::string streamName;

	double Derivative(double);
public:
	SystemNonLinEq(std::function<void(double&,double&)>, double, double, std::string);

	void Grid(double);

	bool Newton();

	void StreamOpen();
	void StreamClose();

	~SystemNonLinEq();
};

