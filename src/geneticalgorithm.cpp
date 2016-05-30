#include "../include/geneticalgorithm.h"
#include "../include/populationcreator.h"
#include "../include/objectivefunction.h"
#include "../include/localsearch.h"
#include <algorithm>


GeneticAlgorithm::GeneticAlgorithm(DataFile data, int popsize, int maxgenerations, double pc, double pm, int seed){
	this->data = data;
	this->popsize = popsize;
	this->maxgenerations = maxgenerations;
	this->pc = pc;
	this->pm = pm;
	this->seed = seed;

	this->generator = std::default_random_engine(seed);
	this->rand_pop = std::uniform_int_distribution<int>(0,popsize);
	this->prob = std::uniform_real_distribution<double>(0,1);
}


bool comp(Solution s1, Solution s2){
	return s1 < s2;
}

Solution GeneticAlgorithm::run(){
	/*Creates an objective function evaluator and a population creator*/
	ObjectiveFunction evaluator(this->data);
	PopulationCreator pcreator(&evaluator, this->popsize, this->data.n(), this->seed);
	
	/*Creates random population as initial set*/
	std::vector<Solution> population = pcreator.randomPopulation();
	
	/*Sorts population in increasing order*/
	sort(population.begin(), population.end(), comp);
	
	
}


std::vector<int> GeneticAlgorithm::tournament(std::vector<Solution> population, int k, int except){
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
	std::vector<bool> placed(p1.size(), false);	

	/*Copy equal positions from parents into child*/
	for(unsigned int i=0;i<p1.size();i++){
		if(p1[i] == p2[i]){
			child[i] = p1[i];
			placed[p1[i]] = true;
		}
	}
	
	/*Assign the rest of the positions according to parents or randomly*/
	for(unsigned int i=0;i<p1.size();i++){
		if(child[i] == -1){
			if(!placed[p1[i]] && !placed[p2[i]]){
				/*If none of the parents position was already placed, choose probabilistically*/
				double p = this->prob(this->generator);
				if( p > 0.5 )
					child[i] = p1[i];
				else
					child[i] = p2[i];
			}else if(!placed[p1[i]]){
				child[i] = p1[i];
			}else if(!placed[p2[i]]){
				child[i] = p2[i];
			}else{
				/*If both positions were placed, choose another randomly*/
				int r = this->rand_pop(this->generator);
				while(placed[r])
					r = this->rand_pop(this->generator);
				child[i] = r;
			}
			
			/*Mark this place as used*/
			placed[child[i]] = true;
		}
	}

	return child;
}	
