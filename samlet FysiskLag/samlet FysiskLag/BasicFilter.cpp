#include "BasicFilter.h"



BasicFilter::BasicFilter(std::vector<double> acoe, std::vector<double> bcoe)
{
	a = acoe;
	b = bcoe;

	if (a.size() != b.size())
	{
		if (a.size() < b.size())
		{
			for (int i = a.size(); i < b.size(); i++)
				a.push_back(0);
		}

		if (a.size() > b.size())
		{
			for (int i = b.size(); i < a.size(); i++)
				b.push_back(0);
		}
	}

	buffer = std::vector<double>(a.size() - 1, 0);
}

double BasicFilter::filter(double xn)
{
	double w = xn * a[0];
	int j = 0;

	for (int i = (a.size() - 1); i > 0; i--)
		w -= a[i] * buffer[j++];

	double y = w * b[0];
	j = 0;

	for (int i = (b.size() - 1); i > 0; i--)
		y += b[i] * buffer[j++];

	buffer.erase(buffer.begin());
	buffer.push_back(w);

	return y;
}

std::vector<double> BasicFilter::getA()
{
	return a;
}

std::vector<double> BasicFilter::getB()
{
	return b;
}


BasicFilter::~BasicFilter()
{}
