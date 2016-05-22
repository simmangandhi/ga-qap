#include "../include/populationcreator.h"

/*Constructor*/
PopulationCreator::PopulationCreator(int popSize, int n, int seed){
	this->popSize = popSize;
	this->nf = n;

	this->generator = std::default_random_engine(seed);
	this->rand = std::uniform_int_distribution<int>(0, n-1);
}

/*Random population creator*/
std::vector<Solution> PopulationCreator::randomPopulation(){
	std::vector<Solution> population;
	
	/*While population is smaller than the parameter 'population size'*/
	while(population.size() < this->popSize){
		std::vector<int> individual;
		std::vector<bool> used(this->nf, false);
		
		/*While individual doesn't have n locations in it*/
		while(individual.size() < this->nf){
			int r = this->rand(this->generator);
			if(!used[r]){
				individual.push_back(r);
				used[r] = true;
			}
		}

		Solution si(individual);
		population.push_back(si);
	}
	
	return population;
}	
