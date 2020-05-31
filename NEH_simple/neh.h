#pragma once

#include <fstream>
#include "helpers.h"

void neh(std::string fileName, std::string dataSet)
{
	//N	-	# of tasks
	//M	-	# of machines
	int N, M;

	//set up file 'f' variable (handler?)
	std::ifstream file(fileName);
	//move till data
	moveTillData(file, dataSet);
	//read ## of tasks and machines
	file >> N >> M;

	//allocate memory for 2D dynamic array
	int** matrixData = new int* [N];
	for (int i = 0; i < N; ++i) {
		matrixData[i] = new int[M];
	}

	//fill shrinkingMatrix w/ data
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			file >> matrixData[i][j];





	//deallocate memory
	for (int i = 0; i < N; ++i) {
		delete[] matrixData[i];
	}
	delete[] matrixData;
}
