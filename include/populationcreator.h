#ifndef POPULATION_CREATOR_H
#define POPULATION_CREATOR_H

#include "solution.h"
#include <random>
#include <vector>

class PopulationCreator{
private:
	/*Size of the population*/
	int popSize;
	/*Number of facilities*/
	int nf;

	/*Variables of the random number generator*/
	std::default_random_engine generator;
	std::uniform_int_distribution<int> rand;

public:
	/*Constructor*/
	PopulationCreator(int popSize, int n, int seed);
	/*Random population creator*/
	std::vector<Solution> randomPopulation();	

};

#endif