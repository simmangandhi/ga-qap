#include "../include/solution.h"
	
Solution::Solution(int nf){
	this->nf = nf;
	this->fitnessf = 0;
	this->permutationf.assign(nf, -1);
}

Solution::Solution(std::vector<int> perm){
	this->nf = perm.size();
	this->fitnessf = 0;
	this->permutationf = perm;
}

std::vector<int> Solution::permutation(){
	return this->permutationf;	
}

int Solution::p(int i){
	return this->permutationf[i];
}

int n(){
	return this->nf;
}

int fitness(){
	return this->fitnessf;
}

void setFitness(int newFitness){
	this->fitnessf = newFitness;
}
