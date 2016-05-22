#include "../include/datafile.h"
#include <cstdio>
#include <iostream>

DataFile::DataFile(){ }

int DataFile::read(std::string filename){
	FILE *file = fopen(filename.c_str(), "rt");

	if(file == NULL)
		return -1;
	
	//reads the number of facilities
	fscanf(file, "%i\n\n", &(this->nf));
	
	this->flowm.assign(this->nf, std::vector<int>(this->nf, 0));
	this->distancem.assign(this->nf, std::vector<int>(this->nf, 0));

	//reads flow and distance matrix
	for(int i=0;i<this->nf;i++)
		for(int j=0;j<this->nf;j++)
			fscanf(file, "%i", &(this->flowm[i][j]));

	for(int i=0;i<this->nf;i++)
		for(int j=0;j<this->nf;j++)
			fscanf(file, "%i", &(this->distancem[i][j]));

	fclose(file);
	return 0;
}

int DataFile::flow(int i, int j){
	return this->flowm[i][j];
}

int DataFile::distance(int i, int j){
	return this->distancem[i][j];
}

int DataFile::n(){
	return this->nf;
}

int DataFile::writeSolution(){
	//TODO: write solution to file
}

void DataFile::printOut(){
	std::cout << "====================================" << std::endl;
	std::cout << "n = " << this->nf << std::endl;
	
	std::cout << "A :" << std::endl;
	for(int i=0;i<this->nf;i++){
		for(int j=0;j<this->nf;j++){
			std::cout << this->flowm[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "B :" << std::endl;
	for(int i=0;i<this->nf;i++){
		for(int j=0;j<this->nf;j++){
			std::cout << this->distancem[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
