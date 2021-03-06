#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

/*Chromossome class of a possible solution to the problem*/
class Solution{
private:
	/*A possible permutation of the facilities between locations*/
	std::vector<int> permutationf;
	/*Number of facilities and locations to be permuted*/
	int nf;
	/*Fitness of this permutation*/
	int fitnessf;

public:
	Solution(int nf=0);
	Solution(std::vector<int> perm);
	std::vector<int> permutation();
	int& operator[](int i);
	int p(int i);
	int n();
	int fitness();
	void setFitness(int newFitness);
	bool operator<(Solution s);
	bool operator<=(Solution s);
	bool operator>(Solution s);
	bool operator>=(Solution s);

};

#endif
