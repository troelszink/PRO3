#include<vector>

#pragma once
class BasicFilter
{
public:
	BasicFilter(std::vector<double> acoe, std::vector<double> bcoe);
	double filter(double xn);
	std::vector<double> getA();
	std::vector<double> getB();
	~BasicFilter();
private:
	std::vector<double> buffer;
	std::vector<double> a;
	std::vector<double> b;
};

