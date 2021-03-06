#include "../include/localsearch.h"
#include <cstdio>
#include <utility>
#include <set>

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
			}
		}
	}
	return s;
}

/*Run a limited iterated local search in solution s*/
Solution LocalSearch::runLimitedIteratedSearch(Solution s, int maxiterations){

	Solution best = s;
	/*Start picking a neighbor of s*/
	s = runAllPairChanges(s);
	if(s < best)
		best = s;	

	int iter = 0;
	int u = 2;
	
	while(iter < maxiterations*0.1){
		iter++;
		/*Perturb the current solution s with u pair changes*/
		s = perturbation(s, u);
		
		/*Updates u variable*/
		u++;
		if(u > data.n()) u = 2;
		
		/*Improves s locally*/
		s = runAllPairChanges(s);

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
		while(v == t)
			v = this->rand_place(*(this->generator));	

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

