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

/*
counting cmax for point matrivData[x[f]][m]
point - counting cmax for this point
f	-	current task
m	-	current machine
matrixData, x	-	data
*/
int cmax(int point, int f, int m, int** matrixData, int* x)
{
	//jestesmy w punkcie (0,0)
	if (m == 0 && f == 0) return matrixData[x[0]][0];
	//jestesmy w pirwszym rzedzie
	if (m == 0) return matrixData[x[f]][m] + cmax(matrixData[x[f-1]][m], f-1, m, matrixData, x);
	//jestesmy w skrajnie lewej kolumnie
	if (f == 0) return matrixData[x[f]][m-1] + cmax(matrixData[x[f]][m-1], f, m-1, matrixData, x);	
	


	int top_cmax = cmax(matrixData[x[f]][m - 1], f, m-1, matrixData, x);
	int top_p = matrixData[x[f]][m - 1];
	int left_cmax = cmax(matrixData[x[f - 1]][m], f-1, m, matrixData, x);
	int left_p = matrixData[x[f-1]][m];


	return std::max(top_cmax + top_p, left_cmax + left_p);
}



int countCmax(int** matrixData, int N, int M, int* x, int f)
{
	int m = M - 1;	//current machine = #M - 1
	int p = matrixData[x[f]][m];	//wartoœæ zadania z Right-Bottm-Corner
	//cmax for BRC task
	int _cmax;
	_cmax = cmax(matrixData[x[f]][m], f, M - 1, matrixData, x);

	return p + _cmax;
}


int countCmax2(int** matrixData, int N, int M, int* x, int f, int** matrixCmax)
{

	for (int n = 0; n <= f; ++n)
		for (int m = 0; m < M; ++m)
		{
			if (n == 0 && m == 0)
				matrixCmax[n][m] = matrixData[x[n]][m];
			else if (n == 0)	//first task/column
				matrixCmax[n][m] = matrixCmax[n][m - 1] + matrixData[x[n]][m];
			else if (m == 0)	//first machine/row
				matrixCmax[n][m] = matrixCmax[n-1][m] + matrixData[x[n]][m];
			else
				matrixCmax[n][m] = std::max(matrixCmax[n-1][m], matrixCmax[n][m - 1]) + matrixData[x[n]][m];
		}



	return matrixCmax[f][M-1];
}