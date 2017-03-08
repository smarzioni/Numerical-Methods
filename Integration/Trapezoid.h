#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cmath>
#include <iostream>

using namespace std;

/* Trapezoid recursive and Iterative methods to compute Integrals. 
  T is a class supposed to have an overloaded operator
  double T::operator() (double)
  This script the computes the integral of f(x) == T(x).
  The Function Trapezoid expect the left and right extremes as arguments. These are supposed
	to be finite.
  The Optional argument LogIterations parametraze the logarithm base 2 of the cardinality 
	of the partition of the interval.
*/

template<class T>
double TrapezoidIterated(const T& TheIntegrand,
	double leftExtreme, // a
	double rightExtreme, // b
	int MaxIterations = 10, //log(2^n)
	double tolerance = 0.1e-5)
{
	double h = (rightExtreme - leftExtreme);
	double integral = 0.5*h*(TheIntegrand(leftExtreme) + TheIntegrand(rightExtreme)); //R(0,0)
	int intervals = 1;
	double pastIntegral = 0;

	for (int i = 1; i <= MaxIterations; i++) //compute R(i,0), i>=1
	{
		if ((fabs(pastIntegral - integral) <= tolerance*fabs(pastIntegral)) && (i > 2))
		{
			//cout << "\nDEBUG : Exit by tolerance, iteration " << i - 1 << "\n";
			return integral;
		}

		double summand = 0;
		h *= 0.5;
		for (int k = 1; k <= intervals; k++)
			summand += TheIntegrand(leftExtreme + (2 * k - 1)* h);
		summand *= h;
		pastIntegral = integral;
		integral *= 0.5;
		integral += summand;
		intervals *= 2;
	}
	return integral;
}


template<class T>
double TrapezoidRecursed(const T& TheIntegrand,
	double leftExtreme, // a
	double rightExtreme, // b
	int LogIterations, //n
	int intervals  ) //2^n
{
	double h = (rightExtreme - leftExtreme) / intervals;
	
	if (LogIterations == 0)
		return 0.5*h*(TheIntegrand(leftExtreme) + TheIntegrand(rightExtreme));

	intervals /= 2; //intervals = 2^(n-1)
	if (LogIterations > 0)
	{
		double summand = 0.0;
		for (int k = 1; k <= intervals; k++) // k =1,... 2^(n-1)
			summand += TheIntegrand(leftExtreme + (2 * k - 1)* h);
		summand *= h;
		return 0.5 * TrapezoidRecursed(TheIntegrand, leftExtreme, rightExtreme, LogIterations - 1, intervals)
			+ summand;
	}
}

template<class T>
double Trapezoid(const T& TheIntegrand,
	double leftExtreme,
	double rightExtreme,
	int LogIntervals = 4)
{
	int intervals = pow(2, LogIntervals);

	return TrapezoidRecursed(TheIntegrand, leftExtreme, rightExtreme, LogIntervals, intervals);
	
}



#endif // !TRAPEZOID_H
