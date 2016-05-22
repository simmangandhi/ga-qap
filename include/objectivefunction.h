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
	int evaluate(Solution s);
	
};

#endif

