#include <vector>
#include "BasicFilter.h"
#pragma once
class KaskadeFilter
{
public:
	KaskadeFilter(std::vector<BasicFilter> filt);
	double filter(double xn);
	~KaskadeFilter();
private:
	std::vector<BasicFilter> filters;
};

