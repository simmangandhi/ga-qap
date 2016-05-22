#include "../include/objectivefunction.h"

ObjectiveFunction::ObjectiveFunction(DataFile data){
	this->data = data;
}

int ObjectiveFunction::evaluate(Solution s){
	int fitness = 0;
	/*Function to minimize*/
	for(int i=0;i<data.n();i++){
		for(int j=0;j<data.n();j++){
			/*There is a flow between two locations i and j, but also there is a distance between facilities p(i) and p(j)*/
			fitness += data.flow(i, j)*data.distance(s.p(i), s.p(j);
		}
	}

	return fitness;
}