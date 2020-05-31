#pragma once

#include <fstream>

//This function moves coursor in file 'fileName' till 'dataNumber' appears
//'fileName' needs to be passed as a reference! (NOT COPIED)
void moveTillData(std::ifstream& fileName, std::string dataSet)
{
	std::string s = "";

	//READ TILL "data.X" phrase
	while (s != (dataSet + ":")) {
		fileName >> s;
	}

}