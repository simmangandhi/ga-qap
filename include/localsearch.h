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
	std::default_random_engine *generator;
	std::uniform_int_distribution<int> rand_place;

	/*Makes u pair perturbations in solution s*/
	Solution perturbation(Solution s, int u);

public:
	LocalSearch(DataFile data, std::default_random_engine *generator);

	/*Run a limited iterated local search in solution s*/
	Solution runLimitedIteratedSearch(Solution s, int maxiterations);

	/*Finds a local minima for this solution changing all pairs (t,u) of places in permutation s*/
	Solution runAllPairChanges(Solution s);


};

#endif
