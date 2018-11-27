#include "KaskadeFilter.h"



KaskadeFilter::KaskadeFilter(std::vector<BasicFilter> filt)
{
	filters = filt;
}


double KaskadeFilter::filter(double xn)
{
	double y = xn;

	for (BasicFilter filt : filters)
		y = filt.filter(y);

	return y;
}

std::vector<BasicFilter> KaskadeFilter::getFilter()
{
	return filters;
}

KaskadeFilter::~KaskadeFilter()
{}
