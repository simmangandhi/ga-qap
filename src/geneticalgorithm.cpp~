#include "../include/geneticalgorithm.h"
#include "../include/populationcreator.h"
#include "../include/localsearch.h"
#include <algorithm>
#include <cstdio>

/*Constructor*/
GeneticAlgorithm::GeneticAlgorithm(DataFile data, int popsize, int maxgenerations, int k, double pc, int seed, bool prints){
	this->data = data;
	this->popsize = popsize;
	this->maxgenerations = maxgenerations;
	this->k = k;
	this->pc = pc;
	this->seed = seed;
	this->prints = prints;

	this->generator = std::default_random_engine(seed);
	this->rand_pop = std::uniform_int_distribution<int>(0,popsize-1);
	this->rand_place = std::uniform_int_distribution<int>(0,data.n()-1);
	this->prob = std::uniform_real_distribution<double>(0,1);
}


bool comp(Solution s1, Solution s2){
	return s1 < s2;
}

Solution GeneticAlgorithm::run(){
	/*Creates an objective function evaluator and a population creator*/
	ObjectiveFunction evaluator(this->data);
	PopulationCreator pcreator(&evaluator, this->popsize, this->data.n(), &this->generator);

	/*Creates random population as initial set*/
	std::vector<Solution> population = pcreator.randomPopulation();
	
	/*Local search object*/
	LocalSearch ls(this->data, &this->generator);
	
	/*Improves locally all the initial solutions*/
	for(int i=0;i<population.size();i++){
		population[i] = ls.runAllPairChanges(population[i]);
	}

	/*Sorts population in increasing order*/
	sort(population.begin(), population.end(), comp);
	/*Selects the best solution*/
	Solution bestSolution = population[0];
	
	if(prints)
	    printf("Best solution in generation 0:  %i\n", bestSolution.fitness());
	
	/*Updates basic information attributes*/
	this->bestSolution = bestSolution;
	this->initialSolution = bestSolution;
	this->iterBest = 0;
	
	/*Initialize basic variables of the GA*/
	int u = 1;
	int lastmutation = 0;
	int mutation_type = 1;
    int generation = 0;
	
	/*GA main loop*/
	while(generation < maxgenerations){
		generation++;

		std::vector<Solution> offspring;
		while(offspring.size() < (unsigned int)popsize*0.5){
			int except = -1;
			/*Tournament to select parents*/
			Solution p1 = tournament(population, this->k, &except);
			Solution p2 = tournament(population, this->k, &except);
			
			/*crossover of parents*/
			Solution c = crossoverOpt(p1, p2, evaluator);

			/*Evaluate c*/
			c.setFitness(evaluator.evaluate(c));
			
			/*Run a limited local search on the new child*/
			c = ls.runLimitedIteratedSearch(c, data.n());	

			offspring.push_back(c);
		}

		/*Sorts offspring in increasing order*/
		sort(offspring.begin(), offspring.end(), comp);
		/*Inserts the best individuals from offspring in the population as long as they are better than the latter*/
		for(unsigned int i=0;i<offspring.size();i++){
			if(offspring[i] < population[popsize-1-i])
				population[popsize-1-i] = offspring[i];
		}
		
		/*Sorts population in increasing order*/
		sort(population.begin(), population.end(), comp);
		
		/*In case population has converged*/
		if(population[0] >= bestSolution && generation - lastmutation > 100 && generation - this->iterBest > 200 && mutation_type==1){ 
			/*First try the shift mutation approach*/
			for(int i=0;i<popsize;i++){
				population[i] = shiftMutation(population[i], u);
				population[i].setFitness(evaluator.evaluate(population[i]));
			}
			if(prints)
				printf("Mutated population with u = %i\n", u);

			u++;
			if(u > data.n()*0.5){
				/*In case the shift mutation has not done the job, go to the second type*/
				u=1;
				mutation_type=2;
			}

			sort(population.begin(), population.end(), comp);
			lastmutation = generation;
		}
		else if(population[0] >= bestSolution && generation - lastmutation > 100 && generation - this->iterBest > 200 && mutation_type==2){
			/*The second approach executes several perturbations in the solutions*/
			if(prints)
				printf("Perturbing solutions...\n");

			for(int i=0;i<popsize;i++){
				for(int j=0;j<data.n()*0.2;j++){
					int r = this->rand_place(this->generator);
					int s = this->rand_place(this->generator);
					while(r == s)
						r = this->rand_place(this->generator);

					population[i].setFitness(evaluator.evaluatePairChange(population[i], r, s));
				
					int temp = population[i][r];
					population[i][r] = population[i][s];
					population[i][s] = temp;
				}
				/*Improves the solutions locally*/
				population[i] = ls.runAllPairChanges(population[i]);
			}
			
			sort(population.begin(), population.end(), comp);
			lastmutation = generation;
			mutation_type = 1;
		}
		
		/*If the new best solution is better than the current one*/
		if(population[0] < bestSolution){
			/*Update the current best solution*/
			bestSolution = population[0];
			this->bestSolution = bestSolution;
			this->iterBest = generation;
			u = 1;
			if(prints)
				printf("Best solution in generation %i:  %i\n", generation, bestSolution.fitness());
		}
	}

	/*Finally, return the best solution found*/
	return bestSolution;
}

/*Tournament selection of size k, except >= 0 is a solution that can't be selected*/
Solution GeneticAlgorithm::tournament(std::vector<Solution> population, int k, int *except){
	/*Selects a random individual from the population that is not the except one*/
	int r = this->rand_pop(this->generator);

	while(r == *except)	
		r = this->rand_pop(this->generator);
	
	Solution selected = population[r];
	*except = r;
	/*Runs the tournament k-1 times and selects the best from this tournament*/
	for(int i=1;i<k;i++){
		r = this->rand_pop(this->generator);
		while(r == *except)	
			r = this->rand_pop(this->generator);
		if(population[r] < selected){
			selected = population[r];
			*except = r;
		}
	}

	/*Returns the best permutation*/
	return selected;
}

/*Crossover of two parents producing one child. Equal positions are kept, while the rest is randomly chosen (the best solution in N*0.2 runs is returned). There is a pc change that crossober occurs, otherwise the best parent is returned*/
Solution GeneticAlgorithm::crossoverOpt(Solution p1, Solution p2, ObjectiveFunction evaluator){
	/*probability of crossover occurring*/
	double pcs = this->prob(this->generator);
	if(pcs > this->pc){ /*if crossover does not occur, return the best parent*/
		if(p1 > p2) return p2;
		else return p1;
	}

	/*The new child*/
	std::vector<int> child(p1.n(), -1);
	/*Vector indicating wheter a given facility was already placed or not*/
	std::vector<bool> placed(p1.n(), false);	

	/*Copy equal positions from parents into child*/
	for(int i=0;i<p1.n();i++){
		if(p1[i] == p2[i]){
			child[i] = p1[i];
			placed[p1[i]] = true;
		}
	}
	
	/*Save the equal positions stored*/
	std::vector<int> childm = child;
	std::vector<bool> placedm = placed;
	Solution *best = NULL;
	/*Tries N*0.2 times*/
    int lim = data.n()*0.2;

	for(int m=0;m<lim;m++){
		child = childm;
		placed = placedm;

		/*Assign the rest of the positions according to parents or randomly*/
		for(int i=0;i<p1.n();i++){
			if(child[i] == -1){
				if(!placed[p1[i]] && !placed[p2[i]]){
					/*If none of the parents position was already placed, choose probabilistically*/
					double p = this->prob(this->generator);
					if( p < 0.5  )
						child[i] = p1[i];
					else
						child[i] = p2[i];
				}else if(!placed[p1[i]]){
					child[i] = p1[i];
				}else if(!placed[p2[i]]){
					child[i] = p2[i];
				}else{
					/*If both positions were placed, choose another randomly*/
					int r = this->rand_place(this->generator);
					while(placed[r])
						r = this->rand_place(this->generator);
					child[i] = r;
				}
			
				/*Mark this place as used*/
				placed[child[i]] = true;
			}
		}
		Solution s(child);
		s.setFitness(evaluator.evaluate(s));

		if(best == NULL){
			best = new Solution(child);
		}else if(*best > s){
			best = new Solution(child);
		}
	}

	return *best;
}	


/*Shift the current solution u positions in a circular way*/
Solution GeneticAlgorithm::shiftMutation(Solution s, int u){
	std::vector<int> p1(u);
	std::vector<int> p2(s.n()-u);

	for(int i=0;i<s.n();i++){
		if(i<u)
			p1[i] = s[i];
		else
			p2[i-u] = s[i];
	}

	for(int i=0;i<s.n();i++){
		if(i<(s.n()-u))
			s[i] = p2[i];
		else
			s[i] = p1[i-(s.n()-u)];
	}
	return s;	
}

Solution GeneticAlgorithm::getInitialSolution(){
	return this->initialSolution;
}

Solution GeneticAlgorithm::getBestSolution(){
	return this->bestSolution;
}

int GeneticAlgorithm::getIterBest(){
	return this->iterBest;
}
