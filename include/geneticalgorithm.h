#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "datafile.h"
#include "solution.h"
#include "../include/objectivefunction.h"
#include <random>
#include <vector>

class GeneticAlgorithm{
private:
	/*The basic data of the problem*/
	DataFile data;
	/*Crossover probability*/
	double pc;
	/*Population size*/
	int popsize;
	/*The tournament size*/
	int k;
	/*Maximum number of generations to run*/
	int maxgenerations;
	/*Random operator seed*/
	int seed;
	/*Indicates wheter prints are allowed or not*/
	bool prints;
	
	Solution bestSolution;
	Solution initialSolution;
	int iterBest;

	/*Variables of the random number generator*/
	std::default_random_engine generator;
	std::uniform_int_distribution<int> rand_pop;
	std::uniform_int_distribution<int> rand_place;
	std::uniform_real_distribution<double> prob;
	
	/*Tournament selection of size k, except >= 0 is a solution that can't be selected*/
	Solution tournament(std::vector<Solution> population, int k, int *except);
	/*Shift the current solution u positions in a circular way*/
	Solution shiftMutation(Solution s, int u);
	/*Crossover of two parents producing one child. Equal positions are kept, while the rest is randomly chosen (the best solution in N*0.2 runs is returned). There is a pc change that crossober occurs, otherwise the best parent is returned*/
	Solution crossoverOpt(Solution p1, Solution p2, ObjectiveFunction evaluator);


public:
	/*Constructor*/
	GeneticAlgorithm(DataFile data, int popsize, int maxgenerations, int k, double pc, int seed, bool prints=false);
	Solution run();
	Solution getInitialSolution();
	Solution getBestSolution();
	int getIterBest();
	

};

#endif
