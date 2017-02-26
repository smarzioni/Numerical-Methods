#ifndef HALTON_H
#define HALTON_H

#include <vector>

/*Generator for a sequence of Halton points in (0,1). It will use automatically the first 'dimension'
 prime numbers.
 Seed is the starting point in the Halton sequence and is updated at each point generation. 
 Use it only for LOW dimension, anyway this script works only for dimension <= 95.
 The method GetNextHaltonPoints generates the elements from seed to seed + size -1 */

class Halton
{
public:
	Halton(unsigned int dimension, unsigned long seed = 1);

	std::vector<std::vector<double>> GetNextHaltonPoints(unsigned int size);
	//Return Halton points points under in a vector of dimensions vector [size][dimension] 
	void SetSeed(unsigned long Seed);
	void SetDimension(unsigned int dim);
	void Reset(unsigned int dimension, unsigned long seed = 1);

private:
	unsigned long Seed;
	unsigned int dimension;
	std::vector<unsigned int> Basis;
	std::vector<std::vector<unsigned int>> SeedExpansions;
	//The vector basis store the first dimension prime number.
	//the vector SeedExpansions is of length dimension and contains integer vectors 
	// corresponding to the expansion of Seed in basis prime number of the same index
};


#endif // !HALTON_H
