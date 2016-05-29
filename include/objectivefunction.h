#ifndef OBJECTIVE_FUNCTION_H
#define OBJECTIVE_FUNCTION_H

#include "datafile.h"
#include "solution.h"

class ObjectiveFunction{
private:
	/*Data information about the problem*/
	DataFile data;
	
public:
	ObjectiveFunction(DataFile data);
	/*Evaluates entire solution s*/
	int evaluate(Solution s);
	/*Evaluates a pair exchange in solution s, where locations in s(i) and s(j) will be exchanged*/
	int evaluatePairChange(Solution s, int i, int j);
	
};

#endif

