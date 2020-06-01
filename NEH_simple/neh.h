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


	//create 1D array that has rows sorted by weight
	//x is orderByWeightDescending
	int* x = new int[N];
	countByWeightDescending(matrixData, N, M, x);

	/* not worth it - problem with index 0
		//negate all = not inserted into simulation yet
	for (int n = 0; n < N; ++n)
		x[n] *= -1;

	*/

	int result;

	//it's corresponding x[] order!
	int** matrixCmax = new int* [N];
	for (int i = 0; i < N; ++i) {
		matrixCmax[i] = new int[M];
	}

	//index how far we are with simulation
	//#f - current N taken into account
	for (int f = 0; f < N; ++f)	//++f wykona siê na koniec pêtli!
	{
		//result = countCmax(matrixData, N, M, x, f);
		// int x[] = { 0, 3, 2, 1 };
		int* x = new int[4];
		x[0] = 0;
		x[1] = 3;
		x[2] = 2;
		x[3] = 1;

		result = countCmax2(matrixData, N, M, x, f, matrixCmax);
		//std::cout << "R= " << result << std::endl;
	}



	for (int i = 0; i < N; ++i) {
		delete[] matrixCmax[i];
	}
	delete[] matrixCmax;


	//deallocate memory
	for (int i = 0; i < N; ++i) {
		delete[] matrixData[i];
	}
	delete[] matrixData;
}
