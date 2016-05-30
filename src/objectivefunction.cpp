#include "../include/objectivefunction.h"
#include <iostream>
ObjectiveFunction::ObjectiveFunction(DataFile data){
	this->data = data;
}

int ObjectiveFunction::evaluate(Solution s){
	int fitness = 0;
	/*Function to minimize*/
	for(int i=0;i<data.n();i++){
		for(int j=0;j<data.n();j++){
			/*There is a flow between two locations i and j, but also there is a distance between facilities p(i) and p(j)*/
			fitness += data.flow(i, j)*data.distance(s[i], s[j]);
		}
	}

	return fitness;
}

/*Evaluates a pair exchange in solution s, where locations in s(i) and s(j) will be exchanged*/
int ObjectiveFunction::evaluatePairChange(Solution s, int i, int j){
	int fitness = s.fitness();
	int delta = 0;	
	
	delta +=  data.flow(i,j)*data.distance(s[i], s[j]);
	delta = delta - data.flow(i,j)*data.distance(s[j], s[i]);
	delta +=  data.flow(j,i)*data.distance(s[j], s[i]);
	delta = delta - data.flow(j,i)*data.distance(s[i], s[j]);

	delta = delta + (2*data.flow(i,i)*data.distance(s[i], s[i]));
	delta = delta - (2*data.flow(i,i)*data.distance(s[j], s[j]));
	delta = delta + (2*data.flow(j,j)*data.distance(s[j], s[j]));
	delta = delta - (2*data.flow(j,j)*data.distance(s[i], s[i]));

	for(int k=0;k<s.n();k++){
		if(k == i || k==j)
			continue;

		delta = delta + data.flow(k, i)*data.distance(s[k], s[i]);
		delta = delta - data.flow(k, i)*data.distance(s[k], s[j]);
		delta = delta + data.flow(i, k)*data.distance(s[i], s[k]);
		delta = delta - data.flow(i, k)*data.distance(s[j], s[k]);

		delta = delta + data.flow(k, j)*data.distance(s[k], s[j]);
		delta = delta - data.flow(k, j)*data.distance(s[k], s[i]);
		delta = delta + data.flow(j, k)*data.distance(s[j], s[k]);
		delta = delta - data.flow(j, k)*data.distance(s[i], s[k]);
	}

	fitness -= delta;
	return fitness;
}
