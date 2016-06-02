#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "datafile.h"
#include "solution.h"
#include <random>
#include <vector>

class GeneticAlgorithm{
private:
	/*The basic data of the problem*/
	DataFile data;
	/*Crossover probability*/
	double pc;
	/*Mutation probability*/
	double pm;
	/*Population size*/
	int popsize;
	/*The tournament size*/
	int k;
	/*Maximum number of generations to run*/
	int maxgenerations;
	/*Random operator seed*/
	int seed;
	
	Solution bestSolution;
	Solution initialSolution;
	int iterBest;

	/*Variables of the random number generator*/
	std::default_random_engine generator;
	std::uniform_int_distribution<int> rand_pop;
	std::uniform_int_distribution<int> rand_place;
	std::uniform_real_distribution<double> prob;
	
	/*Crossover operation*/
	Solution crossover(Solution p1, Solution p2);
	/*Tournament selection of size k, except >= 0 is a solution that can't be selected*/
	Solution tournament(std::vector<Solution> population, int k, int *except);


public:
	GeneticAlgorithm(DataFile data, int popsize, int maxgenerations, int k, double pc, double pm, int seed);
	Solution run();
	Solution getInitialSolution();
	Solution getBestSolution();
	int getIterBest();
	

};

#endif
