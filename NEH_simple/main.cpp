#include <iostream>
#include "neh.h"

int main()
{
	std::cout << "STARTING PROGRAM\n";
	//-------------- EDIT HERE --------------
	std::string dataFile = "neh.data.txt";
	//std::string dataFile = "neh.data_DIFFERENT.txt";
	std::string dataCollection = "data.120";
	//-------------- END OF USER EDIT --------------



	neh(dataFile, dataCollection);


	std::cout << "FINISHING PROGRAM\n";
	return 0;
}
