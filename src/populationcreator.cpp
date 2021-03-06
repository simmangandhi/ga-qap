#include "../include/populationcreator.h"

/*Constructor*/
PopulationCreator::PopulationCreator(ObjectiveFunction *evaluator, int popSize, int n, std::default_random_engine *generator){
	this->popSize = popSize;
	this->nf = n;
	this->evaluator = evaluator;
	this->generator = generator;
	this->rand = std::uniform_int_distribution<int>(0, n-1);
}

/*Random population creator*/
std::vector<Solution> PopulationCreator::randomPopulation(){
	std::vector<Solution> population;
	
	/*While population is smaller than the parameter 'population size'*/
	while(population.size() < (unsigned int)this->popSize){
		std::vector<int> individual;
		std::vector<bool> used(this->nf, false);
		
		/*While individual doesn't have n locations in it*/
		while(individual.size() < (unsigned int)this->nf){
			int r = this->rand(*this->generator);
			if(!used[r]){
				individual.push_back(r);
				used[r] = true;
			}
		}

		Solution si(individual);
		si.setFitness(this->evaluator->evaluate(si));
		population.push_back(si);
	}
	
	return population;
}	
