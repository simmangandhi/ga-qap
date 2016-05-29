#include "../include/geneticalgorithm.h"
#include "../include/populationcreator.h"
#include "../include/objectivefunction.h"

#include <vector>

GeneticAlgorithm::GeneticAlgorithm(DataFile data, int popsize, int maxgenerations, double pc, double pm, int seed){
	this->data = data;
	this->popsize = popsize;
	this->maxgenerations = maxgenerations;
	this->pc = pc;
	this->pm = pm;
	this->seed = seed;

	//TODO: random engine setup
}


Solution GeneticAlgorithm::run(){
	/*Creates an objective function evaluator and a population creator*/
	ObjectiveFunction evaluator(this->data);
	PopulationCreator pcreator(&evaluator, this->popsize, this->data.n(), this->seed);
	
	/*Creates random population as initial set*/
	std::vector<Solution> population = pcreator.randomPopulation();

	//TODO: sort population
	
	
}


std::vector<int> GeneticAlgorithm::tournament(std:vector<Solution> population, int k, int except){
	/*Selects a random individual from the population that is not the except one*/
	int r = this->rand_pop(this->generator);
	while(r == except)	
		r = this->rand_pop(this->generator);
	
	Solution selected = population[r];
	/*Runs the tournament k-1 times and selects the better from this tournament*/
	for(int i=1;i<k;i++){
		r = this->rand_pop(this->generator);
		while(r == except)	
			r = this->rand_pop(this->generator);
		if(population[r] < selected){
			selected = population[r];
		}
	}

	/*Returns the best permutation*/
	return selected.permutation();
}

std::vector<int> GeneticAlgorithm::crossover(std::vector<int> p1, std::vector<int> p2){
	/*The new child*/
	std::vector<int> child(p1.size(), -1);
	/*Vector indicating wheter a given facility was already placed or not*/
	std::vectpr<bool> placed(p1.size(), false);	

	/*Copy equal positions from parents into child*/
	for(int i=0;i<p1.size();i++){
		if(p1[i] == p2[i]){
			child[i] = p1[i];
			placed[p1[i]] = true;
		}
	}

	for(int i=0;i<p1.size();i++){
		if(child[i] == -1){
			if(!placed[p1[i]] && !placed[p2[i]]){
				//TODO: probability to choose p1 or p2 	
			}else if(!placed[p1[i]]){
				child[i] = p1[i];
				placed[p1[i]] = true;
			}else if(!placed[p2[i]]){
				placed[p2[i]] = true;
			}else{
				//TODO: generate random location to place at ith position in child
			}
		}
	}

	return child;
}	
