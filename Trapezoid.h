#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cmath>

using namespace std;

/* Trapezoid recursive method to compute Integrals. 
  T is a class supposed to have an overloaded operator
  double T::operator() (double)
  This script the computes the integral of f(x) == T(x).
  The Function Trapezoid expect the left and right extremes as arguments. These are supposed
	to be finite.
  The Optional argument LogIterations parametraze the logarithm base 2 of the cardinality 
	of the partition of the interval.
*/

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
