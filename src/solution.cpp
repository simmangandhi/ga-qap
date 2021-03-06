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

int& Solution::operator[](int i){
	return this->permutationf[i];
}

int Solution::p(int i){
	return this->permutationf[i];
}

int Solution::n(){
	return this->nf;
}

int Solution::fitness(){
	return this->fitnessf;
}

void Solution::setFitness(int newFitness){
	this->fitnessf = newFitness;
}

bool Solution::operator<(Solution s){
	return this->fitness() < s.fitness();
}

bool Solution::operator<=(Solution s){
	return this->fitness() <= s.fitness();
}

bool Solution::operator>(Solution s){
	return this->fitness() > s.fitness();
}

bool Solution::operator>=(Solution s){
	return this->fitness() >= s.fitness();
}
