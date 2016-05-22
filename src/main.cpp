#include "../include/datafile.h"
#include <iostream>

using namespace std;
int main(){
	DataFile data;

	if(data.read("./instances/qapdata/bur26a.dat") == -1){
		cout << "Error opening file." << endl;
		return -1;
	}

	//data.printOut();
}

