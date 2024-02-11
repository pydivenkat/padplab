#include <iostream>
#include <cstdlib>
#include <omp.h>

#define DIM 1000

using namespace std;

int main(int argc, char** argv)
{
	int** A = new int*[DIM];
	for (int i = 0; i < DIM; i++)
		A[i] = new int[DIM];
	
	int** B = new int*[DIM];
	for (int i = 0; i < DIM; i++)
		B[i] = new int[DIM];
	
	int** C = new int*[DIM];
	for (int i = 0; i < DIM; i++)
		C[i] = new int[DIM];
		
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			A[i][j] = rand() % 10;
	}
	
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			B[i][j] = rand() % 10;
	}
	
	/*
	cout << "A is " << endl;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	
	cout << "B is " << endl;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			cout << B[i][j] << " ";
		cout << endl;
	}
	*/
	int i, j, k;
	
	double t = omp_get_wtime();
	
	#pragma omp parallel for num_threads(8) private(j, k)
	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			for (k = 0; k < DIM; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}
	
	/*
	cout << "C is " << endl;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
			cout << C[i][j] << " ";
		cout << endl;
	}
	*/
	
	t = omp_get_wtime() - t;
	cout << "Time = " << t << endl;
	
	for (int i = 0; i < DIM; i++)
		delete[] A[i];
	delete[] A;

	for (int i = 0; i < DIM; i++)
		delete[] B[i];
	delete[] B;
	
	for (int i = 0; i < DIM; i++)
		delete[] C[i];
	delete[] C;
	
}
