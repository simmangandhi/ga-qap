#include "../include/localsearch.h"
#include <cstdio>
#include <utility>
#include <set>

LocalSearch::LocalSearch(DataFile data, int seed){
	this->data = data;
	this->seed = seed+1;
	this->evaluator = new ObjectiveFunction(data);
	
	this->generator = new std::default_random_engine(seed);
	this->rand_place = std::uniform_int_distribution<int>(0,data.n()-1);	
}

LocalSearch::LocalSearch(DataFile data, std::default_random_engine *generator){
	this->data = data;
	this->evaluator = new ObjectiveFunction(data);
	
	this->generator = generator;
	this->rand_place = std::uniform_int_distribution<int>(0,data.n()-1);	
}

/*Finds a local minima for this solution changing all pairs (t,u) of places in permutation s*/
Solution LocalSearch::runAllPairChanges(Solution s){
	for(int t=0;t<s.n();t++){
		for(int u=t+1;u<s.n();u++){
			int f = evaluator->evaluatePairChange(s, t, u);

			if(f < s.fitness()){
				int temp = s[t];
				s[t] = s[u];
				s[u] = temp;
				s.setFitness(f);
				t=0;
				break;
			}
		}
	}
	return s;
}

/*Run a limited iterated local search in solution s*/
Solution LocalSearch::runLimitedIteratedSearch(Solution s, int maxiterations){
	/*Maximum number of iterations of the limited pair change*/
	int lpcmaxiter = data.n();
	Solution best = s;
	/*Start picking a neighbor of s*/
	s = runLimitedPairChanges(s, lpcmaxiter);

	if(s < best)
		best = s;	

	int iter = 0;
	int u = 2;
	
	while(iter < maxiterations){
		iter++;
		s = perturbation(s, u);
		u++;
		if(u > 15) u = 2;
		s = runLimitedPairChanges(s, lpcmaxiter);
		if(s < best)
			best = s;
		else
			s = best;
	}	

	return best;
}

/*Makes u pair perturbations in solution s*/
Solution LocalSearch::perturbation(Solution s, int u){
	int p = 0;
	
	while(p < u){
		p++;
		/*Pick two locations randomly*/
		int t = this->rand_place(*(this->generator));
		int v = this->rand_place(*(this->generator));	
		/*Evaluate the exchange*/
		int f = evaluator->evaluatePairChange(s, t, v);
		/*Exhcange points (wheter it is better or not)*/
		s.setFitness(f);
		int temp = s[t];
		s[t] = s[v];
		s[v] = temp;
	}

	return s;
}


/*A limited local search with memory to improve the current solution*/
Solution LocalSearch::runLimitedPairChanges(Solution s, int maxiterations){
	int iter=0;
	/*The local search memory to avoid repeating changes*/
	std::set< std::pair<int, int> > memory;
	/*Maximum number of tries to generate a new pair of random places*/
	int maxtries = ((data.n()*(data.n()-1))/2);
	while(iter < maxiterations){
		iter++;
		int t = this->rand_place(*(this->generator));
		int u = this->rand_place(*(this->generator));
		int tries = 0;

		/*While the movemnt was already tried*/
		while(t == u || memory.count(std::make_pair(t,u)) == 1){
			tries++;
			if(tries >= maxtries)/*Avoid infinite loop*/
				return s;
			t = this->rand_place(*(this->generator));
			u = this->rand_place(*(this->generator));
		}
		
		int f = evaluator->evaluatePairChange(s, t, u);	

		if(f < s.fitness()){
			int temp = s[t];
			s[t] = s[u];
			s[u] = temp;
			s.setFitness(f);
		}

		memory.insert(std::make_pair(t, u));
	}

	return s;
}
