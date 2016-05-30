#include "../include/datafile.h"
#include "../include/solution.h"
#include "../include/populationcreator.h"
#include "../include/objectivefunction.h"
#include "../include/localsearch.h"
#include "../include/geneticalgorithm.h"
#include <iostream>
#include <cstdio>

using namespace std;
int main(){
	DataFile data;

	if(data.read("./instances/qapdata/tai17a.dat") == -1){
		cout << "Error opening file." << endl;
		return -1;
	}

	GeneticAlgorithm ga(data, data.n()*2, 5000, 4, 0.7, 0.01, 80);
	LocalSearch ls(data, 80);

	Solution best = ga.run();
	printf("Initial Solution = %i\n", ga.getInitialSolution().fitness());
	printf("Initial LSC = %i\n", ls.runAllPairChanges(ga.getInitialSolution()).fitness());
	printf("Best Solution Found = %i \n", best.fitness());
	ObjectiveFunction of(data);
	printf("Real BSF = %i\n", of.evaluate(best));
	//data.printOut();
	cout << "Success!" << endl;
	return 0;
}

