#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "datafile.h"
#include "solution.h"
#include "objectivefunction.h"
#include <random>
#include <vector>

class LocalSearch{
private:
	/*Basic data needed*/
	DataFile data;
	/*Random seed*/
	int seed;
	/*Evaluator*/
	ObjectiveFunction *evaluator;

	/*Variables of the random number generator*/
	std::default_random_engine generator;
	std::uniform_int_distribution<int> rand_place;

	
public:
	LocalSearch(DataFile data, int seed);
	/*Finds a local minima for this solution*/
	Solution runComplete(Solution s);

};

#endif
