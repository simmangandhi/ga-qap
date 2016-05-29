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

	for(int k=0;k<s.n();k++){
		if(k == i || k==j){
			int l = i;
			if(k == i) l = j;
			std::cout << "a(k,k)=" << data.flow(k,k) << std::endl;
			std::cout << "b(o(k),o(k))=" << data.distance(s[k],s[k]) << std::endl;
			delta -= 2*data.flow(k,k)*data.distance(s[k], s[k]);
			delta += 2*data.flow(k,k)*data.distance(s[l], s[l]);
			continue;
		}
		delta += (data.flow(k, i)-data.flow(k, j))*(data.distance(s[k], s[i])-data.distance(s[k], s[j]));
		delta += (data.flow(i, k)-data.flow(j, k))*(data.distance(s[i], s[k])-data.distance(s[j], s[k]));
	}
	fitness -= delta;
	return fitness;
}
