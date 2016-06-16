#include "../include/datafile.h"
#include "../include/solution.h"
#include "../include/populationcreator.h"
#include "../include/objectivefunction.h"
#include "../include/localsearch.h"
#include "../include/geneticalgorithm.h"
#include <time.h>
#include <iostream>
#include <cstdio>

using namespace std;

char *input_file = NULL;
char *output_file = NULL;
int pop_size = -1;
int max_iterations = 3000;
int tournament_size = 4;
double cross_p = 0.7;
int seed = 1;
bool prints = false;

/*Reads the parameter for the problem*/
void readParameter(int argc, char **argv);

int main(int argc, char **argv){
	/*Read input parameters*/
	readParameter(argc, argv);
	DataFile data;
	
	//"./instances/qapdata/wil50.dat"

	if(data.read(input_file) == -1){
		printf("Error operning file \'%s\'.\n", input_file);
		return -1;
	}
	
	if(pop_size < 0)
		pop_size = data.n()*0.5;

	GeneticAlgorithm ga(data, pop_size, max_iterations, tournament_size, cross_p, seed, prints);

	Solution best = ga.run();
	
	if(prints){
		printf("Initial Solution = %i\n", ga.getInitialSolution().fitness());
		printf("Best Solution Found = %i \n", best.fitness());
	}
	
	if(output_file != NULL){
		if(data.writeSolution(output_file, best) < 0){
			printf("Failed to save solution to \'%s\'.\n", output_file);
			return -1;
		}
		if(prints)
			printf("Solution saved to \'%s\'.\n", output_file);
	}
	
	if(prints)
		printf("Success!\n");

	return 0;
}



/*Reads the parameter for the problem*/
void readParameter(int argc, char **argv){

	if(argc < 3){
		cout << "Usage:\n" << argv[0] << " -f [input file path]" << endl;
		exit(-1);
	}

	int i=1;
	if(argv[i][0] != '-'){
		cout << "Parameter " << argv[i] << "not defined." << endl;
		exit(-1);
	}else if(argv[i][1] != 'f'){
		cout << "Expected first parameter -f [input file path], found " << argv[i] << "." << endl;
		exit(-1);
	}

	i++;
	input_file = argv[i]; //input file path

	for(i=3;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'p'://population size
					i++;
					pop_size = atoi(argv[i]);
					break;
				case 's'://random seed
					i++;
					seed = atoi(argv[i]);
					break;
				case 'i'://max iterations
					i++;
					max_iterations = atoi(argv[i]);
					break;
				case 'c'://crossover probability
					i++;
					cross_p = atof(argv[i]);
					break;
				case 'k'://tournament size
					i++;
					tournament_size = atoi(argv[i]);
					break;
				case 'o'://output file path
					i++;
					output_file = argv[i];
					break;
				case 'm'://print out allowed
					prints = true;
					break;
				default:
					cout << "Parameter " << argv[i] << "not defined." << endl;
					exit(-1);
			}
		}else{
			cout << "Parameter " << argv[i] << "not defined." << endl;
			exit(-1);
		}
	}
}




