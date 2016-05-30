#include "../include/datafile.h"
#include "../include/solution.h"
#include "../include/populationcreator.h"
#include "../include/objectivefunction.h"
#include "../include/localsearch.h"
#include <iostream>

using namespace std;
int main(){
	DataFile data;

	if(data.read("./instances/qapdata/bur26a.dat") == -1){
		cout << "Error opening file." << endl;
		return -1;
	}

	ObjectiveFunction of(data);
	PopulationCreator pc(&of, 2, data.n(), 9); 

	Solution s = pc.randomPopulation()[0];
	LocalSearch ls(data, 9);
	cout << "Initial:  " << s.fitness() << endl;
	s = ls.runComplete(s);
	cout << "Final:  " << s.fitness() << endl;
	cout << "Real:  " << of.evaluate(s) << endl;

	//data.printOut();
	cout << "Success!" << endl;
}

