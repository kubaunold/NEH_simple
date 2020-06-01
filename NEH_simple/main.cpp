#include <iostream>
#include "neh.h"

int main()
{
	std::cout << "STARTING PROGRAM\n";
	//-------------- EDIT HERE --------------
	std::string dataFile = "neh.data.txt";
	std::string dataCollection = "data.000";
	//-------------- END OF USER EDIT --------------



	neh(dataFile, dataCollection);


	std::cout << "FINISHING PROGRAM\n";
	return 0;
}
