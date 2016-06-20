#ifndef DATA_FILE_H
#define DATA_FILE_H

#include <vector>
#include <string>
#include "solution.h"

class DataFile {
private:
	/*Flow and Distance matrix (usually matrix A and B in the MIP formulation)*/
	std::vector< std::vector<int> > flowm;
	std::vector< std::vector<int> > distancem;
	/*Number of facilities to install*/
	int nf;


public:
	DataFile();
	int read(std::string filename);
	int flow(int i, int j);
	int distance(int i, int j);
	int n();
	int writeSolution(std::string filename, Solution s);
	void printOut();

	int sol;


};

#endif
