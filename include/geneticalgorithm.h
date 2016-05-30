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
	/*Maximum number of generations to run*/
	int maxgenerations;
	/*Random operator seed*/
	int seed;

	/*Variables of the random number generator*/
	std::default_random_engine generator;
	std::uniform_int_distribution<int> rand_pop;
	std::uniform_real_distribution<double> prob;
	
	/*Crossover operation*/
	std::vector<int> crossover(std::vector<int> p1, std::vector<int> p2);
	/*Tournament selection of size k, except >= 0 is a solution that can't be selected*/
	std::vector<int> tournament(std::vector<Solution> population, int k, int except=-1);


public:
	GeneticAlgorithm(DataFile data, int popsize, int maxgenerations, double pc, double pm, int seed);
	Solution run();
	

};

#endif
