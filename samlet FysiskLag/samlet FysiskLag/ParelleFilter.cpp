#include "ParelleFilter.h"



ParelleFilter::ParelleFilter(vector<BasicFilter> filt)
{
	filters1 = filt;
	threadToFilters = new future<double>[filters1.size()];
}

ParelleFilter::ParelleFilter(vector<KaskadeFilter> filt)
{
	filters2 = filt;
	threadToFilters = new future<double>[filters2.size()];
}
double ParelleFilter::filter(double xn)
{	
	double y = 0;
	if (0 < filters1.size())
	{
		for (int i = 0; i < filters1.size(); i++)
			threadToFilters[i] = async(launch::async, &BasicFilter::filter, filters1[i], xn);
		for (int i = 0; i < filters2.size(); i++)
			y += threadToFilters[i].get();
	}
	else if (0 < filters2.size())
	{
		for (int i = 0; i <filters2.size(); i++)
			threadToFilters[i] = async(launch::async, &KaskadeFilter::filter, filters2[i], xn);
		
		for (int i = 0; i < filters2.size(); i++)
			y += threadToFilters[i].get();
		
	}
	else
		throw "Error";

	return y;
}

vector<BasicFilter> ParelleFilter::getfilter1()
{
	return filters1;
}

vector<KaskadeFilter> ParelleFilter::getfilter2()
{
	return filters2;
}


ParelleFilter::~ParelleFilter()
{}
