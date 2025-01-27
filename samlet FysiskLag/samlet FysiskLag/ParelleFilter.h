#include <thread>
#include <future>
#include <vector>

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
	~ParelleFilter();
private:
	vector<BasicFilter> filters1;
	vector<KaskadeFilter> filters2;
	//vector<future<double>> threadToFilters;
};

