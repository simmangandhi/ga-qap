#include "../include/localsearch.h"
#include <iostream>
LocalSearch::LocalSearch(DataFile data, int seed){
	this->data = data;
	this->seed = seed+1;
	this->evaluator = new ObjectiveFunction(data);
	//TODO: initiate random engines
	
}

/*Finds a local minima for this solution*/
Solution LocalSearch::runComplete(Solution s){
	for(int i=0;i<s.n();i++){
		for(int j=i+1;j<s.n();j++){
			int f = evaluator->evaluatePairChange(s, i, j);
			//std::cout << "F = " << f << std::endl;
			if(f < 0){
				std::cout << " SMALLER THAN ZERO" << std::endl;
				return s;
			}
			if(f < s.fitness()){
				int temp = s[i];
				s[i] = s[j];
				s[j] = temp;
				s.setFitness(f);
				i=0;
				break;
			}
		}
	}
	return s;
}
