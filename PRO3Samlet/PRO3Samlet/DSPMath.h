#include <array>
#include <string>
#include <algorithm>
#include <exception>
#include <complex>
#include <vector>
#include <thread>
#include <future>
#pragma once
using namespace std;
class DSPMath
{
public:
	DSPMath();
	enum findTypes { BELOW, ABOVE, EQUAL, BELOWandEQUAL, ABOVEandEQUAL };

	
	vector<complex<double>> fft(vector<complex<double>> signal);
	vector<complex<double>> DTF(vector<double> signal);
	vector<complex<double>> DTF(vector<complex<double>> signal, vector<int> mValues);
	vector<complex<double>> toComplex(vector<double> x);
	vector<double> amplitude(vector<complex<double>> x);
	vector<complex<double>> zeroPadding(vector<complex<double>> x, int padding);
	
	vector<unsigned int> find(vector<double> arr, int threshold, findTypes type);
	

	vector<double> linspace(double begin, double end, int size);
	~DSPMath();
private:
	string replaceInString(string str, string from, string to);
	double pi = 2 * asin(1);
	complex<double> j = (0,1);
	int cnt = 0;
	int cnt2 = 0;
};

