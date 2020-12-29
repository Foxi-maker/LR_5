#pragma once


class NonLinEq
{
	std::function<double(double)> fun;
	std::vector<double> local;						//����������� ������
	std::vector<double> roots;						//������ ������
	

	double left, right;

	static std::fstream stream;
	std::string streamName;	

	double Derivative(double);
public:
	NonLinEq(std::function<double(double)>, double, double, std::string);

	void LocalizationRoots();

	bool Bisection();
	bool Newton();

	void StreamOpen();
	void StreamClose();

	~NonLinEq();
};

