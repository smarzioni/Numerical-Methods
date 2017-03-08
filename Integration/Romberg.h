#ifndef ROMBERG_H
#define ROMBERG_H

#define MAX_LOG_INTERVAL 32
#include "Trapezoid.h"
#include <cmath>

/* Romberg method to compute Integrals.
T is a class supposed to have an overloaded operator
double T::operator() (double)
This script the computes the integral of f(x) == T(x).
The Function Romberg expect the left and right extremes as arguments. These are supposed
to be finite.
The Optional argument LogIterations parametraze the logarithm base 2 of the cardinality
of the partition of the interval.
The optional parameter tolerance gives the minimum relative error between two consectutive
 iterations at which the method stops.
*/

using namespace std;

template<class T> //Computes successice R(n,m)
double Romberg(const T& TheIntegrand, 
	double leftExtreme,
	double rightExtreme,
	unsigned int logIntervals = 4, // max n, 2^n intervals
	double tolerance = 0.1e-6) // Relative error
{
	int intervals = 1;
	double R[MAX_LOG_INTERVAL][MAX_LOG_INTERVAL]; 
	double h = (rightExtreme - leftExtreme);
	R[0][0] = 0.5*h*(TheIntegrand(leftExtreme) + TheIntegrand(rightExtreme)); //R(0,0)

	for (int i = 1; i <= logIntervals; i++) //compute R(i,0), i>=1
	{
		if ((fabs(R[i-1][i-1] - R[i-2][i-2]) <= tolerance*fabs(R[i-2][i-2])) && (i > 2))
		{
			cout << "\nDEBUG : Exit by tolerance, iteration: " << i - 1 << "\n";
			return R[i-1][i-1];
		}

		double summand = 0;
		h *= 0.5;
		for (int k = 1; k <= intervals; k++)
			summand += TheIntegrand(leftExtreme + (2 * k - 1)* h);
		summand *= h;

		R[i][ 0] = 0.5*R[i - 1][0] + summand;
		intervals *= 2;

		double  pov = 4.0;
		for (int j = 1; j <= i; j++)
		{
			R[i][j] = pov*R[i][j-1] - R[i-1][j-1];
			R[i][j] /= (pov-1);
			pov *= 4;
		}
	}
	return R[logIntervals][logIntervals];
}

#endif // !ROMBERG_H
