#ifndef PARK_MILLER_H
#define PARK_MILLER_H


/* ParkMiller is a class for uniform random number generation which follows Park Miller algorithm.
*/

class ParkMiller
{
public:
	ParkMiller(long seed = 1);

	long GetOneRandomInteger();
	void SetSeed(long Seed);

	static unsigned long Max();
	static unsigned long Min();

private:
	long Seed;
};

#endif // !PARK_MILLER_H
