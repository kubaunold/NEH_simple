#pragma once

#include <fstream>
#include <algorithm> 

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



bool weightDescending(int* one, int* two)
{
	return (one[1] > two[1]);
}

//counts total weight of a task and writes to corresponding index in orderByWeightDescending array
void countByWeightDescending(int** matrixData, int N, int M, int* orderByWeightDescending)
{
	//N x 2 array
	//1st row - index
	//2nd row - columnWeight
	//int rows= 2;
	int** weightsBeforeOrderMatrix = new int* [N];
	for (int n = 0; n < N; ++n) {
		weightsBeforeOrderMatrix[n] = new int[2];
	}

	for (int n = 0; n < N; ++n)
	{
		int columnWeight = 0;
		for (int m = 0; m < M; ++m)
		{
			columnWeight += matrixData[n][m];
		}

		weightsBeforeOrderMatrix[n][0] = n;	//index
		weightsBeforeOrderMatrix[n][1] = columnWeight;	//columnWeight
	}

	std::sort(weightsBeforeOrderMatrix, weightsBeforeOrderMatrix + N, weightDescending);
	//alternatively
	//std::sort(std::begin(weightsBeforeOrderMatrix), std::end(weightsBeforeOrderMatrix));

	for (int n = 0; n < N; ++n)
		orderByWeightDescending[n] = weightsBeforeOrderMatrix[n][0];


	for (int i = 0; i < N; ++i) {
		delete[] weightsBeforeOrderMatrix[i];
	}
	delete[] weightsBeforeOrderMatrix;
}