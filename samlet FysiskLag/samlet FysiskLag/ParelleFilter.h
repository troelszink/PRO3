#include <thread>
#include <future>
#include <vector>
#include <array>

#include "BasicFilter.h"
#include "KaskadeFilter.h"
using namespace std;

#pragma once
class ParelleFilter
{
public:
	ParelleFilter(vector<BasicFilter> filt);
	ParelleFilter(vector<KaskadeFilter> filt);
	double filter(double xn);
	vector<BasicFilter> getfilter1();
	vector<KaskadeFilter> getfilter2();
	~ParelleFilter();
private:
	vector<BasicFilter> filters1;
	vector<KaskadeFilter> filters2;
	future<double> * threadToFilters;
};

