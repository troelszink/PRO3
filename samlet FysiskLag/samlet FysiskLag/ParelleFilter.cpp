#include "ParelleFilter.h"



ParelleFilter::ParelleFilter(vector<BasicFilter> filt)
{
	filters1 = filt;
}

ParelleFilter::ParelleFilter(vector<KaskadeFilter> filt)
{
	filters2 = filt;
}
double ParelleFilter::filter(double xn)
{
//	if (0 < filters1.size())
//	{
//		for (BasicFilter filt : filters1)
//		{
////			threadToFilters.push_back(async(launch::async, filt.filter, xn));
//		}
//	}
//	else if (0 < filters2.size())
//	{
//		for (KaskadeFilter filt : filters2)
//		{
////			threadToFilters.push_back(async(launch::async, filt.filter, xn));
//		}
//	}
//
//	double y = 0;
//	
//	for (int i = 0; i < threadToFilters.size(); i++){
//		y += threadToFilters[i].get();
//	}
//
//	threadToFilters.clear();
//	return y;
	return 0;
}


ParelleFilter::~ParelleFilter()
{}
