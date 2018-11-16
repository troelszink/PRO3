#include "DSPMath.h"
#include <iostream>

DSPMath::DSPMath()
{}

vector<complex<double>> DSPMath::fft(vector<complex<double>> signal)
{
	int N = signal.size();
	if (N == 1)
		return signal;
	else if (N == 0)
		return vector<complex<double>>();
	else
	{
		int M = N / 2;
		vector<complex<double>> Even;
		vector<complex<double>> Odd;

		for (int i = 0; i < N; i++)
		{
			if (i % 2 == 0)
				Even.push_back(signal[i]);
			else
				Odd.push_back(signal[i]);
		}
		

		vector<complex<double>> fEven(M, 0);
		vector<complex<double>> fOdd(M, 0);

		fEven = fft(Even);
		fOdd = fft(Odd);

		vector<complex<double>> c(N, 0);
		
		for (int l = 0; l < N/2; l++)
		{
			
			complex<double> oddW = fOdd[l] * polar(1.0, -2 * pi*l / N);
			c[l] = fEven[l] + oddW;
			c[l + N / 2] = fEven[l] - oddW;
		
		}

		return c;
	}

}

vector<complex<double>> DSPMath::DTF(vector<double> signal)
{
	int N = signal.size();

	if (N == 1)
	{
		complex<double> k(1, 0);
		vector<complex<double>> l(1, 0);
		l[0] = (k*signal[0]);
		return l;
	}
	complex<double> j(0, 1);
	complex<double> tmp;

	vector<complex<double>> returnVector(N, 0);
	for (int m = 0; m < N; m++)
	{
		for (int n = 0; n < N; n++)
		{
			tmp += signal[n] * exp(-j * (m * 2 * pi*n) / (double) N);
		}
		returnVector[m] = tmp;
		tmp = 0;
	}

	return returnVector;
}

vector<complex<double>> DSPMath::DTF(vector<complex<double>> signal, vector<int> mValues)
{
	int N = signal.size();

	if (N == 1)
	{
		complex<double> k(1, 0);
		vector<complex<double>> l(1, 0);
		l[0] = (k*signal[0]);
		return l;
	}
	complex<double> j(0, 1);
	complex<double> tmp;

	vector<complex<double>> returnVector;
	for (int m : mValues)
	{
		for (int n = 0; n < N; n++)
		{
			tmp += signal[n] * exp(-j * (m * 2 * pi*n) / (double) N);
		}
		returnVector.push_back(tmp);
		tmp = 0;
	}

	return returnVector;

}


vector<complex<double>> DSPMath::toComplex(vector<double> x)
{
	vector<complex<double>> result(x.size(),0);
	for (int i = 0; i < result.size(); i++)
		result[i] = complex<double>(x[i]);
	return  result;
}

vector<double> DSPMath::amplitude(vector<complex<double>> x)
{	
	vector<double> result;
	for (int i = 0; i < x.size(); i++)
		result.push_back(abs(x[i]));

	return result;
}

vector<complex<double>> DSPMath::zeroPadding(vector<complex<double>> x, int padding)
{
	int t = padding - x.size();

	for (int i = 0; i < t; i++)
		x.push_back(0);

	return x;
}

vector<unsigned int> DSPMath::find(vector<double> arr, int threshold, findTypes type)
{
	vector<unsigned int> result;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i] < threshold && type == BELOW)
			result.push_back(i);
		else if (arr[i] > threshold && type == ABOVE)
			result.push_back(i);
		else if (arr[i] == threshold && type == EQUAL)
			result.push_back(i);
		else if (arr[i] <= threshold && type == BELOWandEQUAL)
			result.push_back(i);
		else if (threshold <= arr[i] && type == ABOVEandEQUAL)
			result.push_back(i);
	}
	return result;
}


vector<double> DSPMath::linspace(double begin, double end, int size)
{
	vector<double> result;
	double stepsize = (end - begin) / (size - 1);
	for (int i = 0; i < size; i++)
		result.push_back(begin + stepsize * i);
	return result;
}

DSPMath::~DSPMath()
{}

string DSPMath::replaceInString(string str, string from, string to)
{
	string replaced;
	for (int i = 0; i <= str.length(); i++)
	{
		if (from.length() <= (str.length() - i))
		{
			string tmp = str.substr(i, from.length());
			if (tmp.compare(from) == 0)
			{
				replaced += to;
			}
			else
				replaced += tmp;
		}
		else
			replaced += str[i];
	}
	return replaced;
}
