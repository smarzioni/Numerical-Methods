
#include "ParkMiller.h"

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

ParkMiller::ParkMiller(long Seed_) : Seed(Seed_)
{
	if (Seed == 0)
		Seed = 1;
}

void ParkMiller::SetSeed(long Seed_)
{
	Seed = Seed_;
	if (Seed == 0)
		Seed = 1;
}

unsigned long ParkMiller::Max()
{
	return m - 1;
}

unsigned long ParkMiller::Min()
{
	return 1;
}

long ParkMiller::GetOneRandomInteger()
{
	// one would like to return Seed * a mod m; Limitation on number lengths force to use the following
	// simple trick (the problem is that, for Seed = m-1, (m-1)*a > 2^31 -1 (32-bit max integer)
	long k;
	
	// m = a*q + r
	// In exact arithmetic Seed = k*q + p (numbers are truncated to int in C++)
	k = Seed / q; 
	
	Seed = a*(Seed - k*q) - r*k;
	// a*(Seed - k*q) - r*k = a*(Seed - Seed + p) - (m - a*q)*k = a*p + a*q*k - m*k = 
	// = a*p +a*(Seed -p) - m*k = a *Seed - m*k.
	// The last expression is obviously a*Seed mod m.
	// The choice of q and r (which is standard from the literature) is such that all the operation 
	// actually made are insade the 32-bit range.

	if (Seed < 0)
		Seed += m;

	return Seed;
}
