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

KaskadeFilter::~KaskadeFilter()
{}
