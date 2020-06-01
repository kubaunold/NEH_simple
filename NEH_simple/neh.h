#pragma once

#include <fstream>
#include "helpers.h"
#include <chrono>


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

	auto start = std::chrono::steady_clock::now();

	//create 1D array that has rows sorted by weight
	//x is orderByWeightDescending
	int* x = new int[N];
	countByWeightDescending(matrixData, N, M, x);

	/* not worth it - problem with index 0
		//negate all = not inserted into simulation yet
	for (int n = 0; n < N; ++n)
		x[n] *= -1;

	*/


	//it's corresponding x[] order!
	int** matrixCmax = new int* [N];
	for (int i = 0; i < N; ++i) {
		matrixCmax[i] = new int[M];
	}



	int finalResult;


	//index how far we are with simulation
	//#f - current N taken into account
	for (int f = 0; f < N; ++f)	//++f wykona siê na koniec pêtli!
	{
		int bestResult = INT_MAX;
		int* bestX = new int[N];

		//i	-	# of swaps
		for (int i = 0; i <= f; ++i)
		{
			int currentResult = countCmax2(matrixData, N, M, x, f, matrixCmax);
			if (currentResult < bestResult)
			{
				bestResult = currentResult;
				for (int n = 0; n <= f; ++n)
					bestX[n] = x[n];
			}

			if (f - i > 0)
				std::swap(x[f - i], x[f - i - 1]);
			else if (f - i == 0)
				std::swap(x[0], x[f]);
		}
		//now I have bestResult and bestX evaluated
		finalResult = bestResult;
		for (int n = 0; n <= f; ++n)
			x[n] = bestX[n];

		//for (int n = 0; n <= f; ++n)
		//	std::cout << x[n] << ' ';
		//std::cout <<"; R= " << finalResult << std::endl;


		delete bestX;

	}

	auto end = std::chrono::steady_clock::now();

	std::cout << "Elapsed time in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;


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
