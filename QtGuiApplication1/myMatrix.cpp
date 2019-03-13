
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
# include "systemfunction.h"
//#include "gnuplot-iostream.h"
using namespace std;


int arraySize(float* a) {
	return _msize(a) / sizeof(a[0]);
}
int arrayRow(float** a) {
	return  _msize(a) / sizeof(a[0]);

}
int arrayCol(float** a) {
	return _msize(a[0]) / sizeof(a[0][0]);
}
float** multi(float** a, float n) {
	int rowA = arrayRow(a);
	int colA = arrayCol(a);


	float** mat = new float*[rowA];
	for (int i = 0; i < rowA; i++) {
		mat[i] = new float[colA];
	}

	for (int i = 0; i < rowA; i++) {
		for (int j = 0; j < colA; j++) {
			mat[i][j] = a[i][j] * n;
		}
	}
	return mat;
}
float** multi(float** a, float** b) {
	int rowA = arrayRow(a);
	int colA = arrayCol(a);
	int rowB = arrayRow(b);
	int colB = arrayCol(b);
	if (colA != rowB)throw "Dimension not match!";

	float** product = new float*[rowA];
	for (int i = 0; i < rowA; ++i)
		product[i] = new float[colB];
	for (int i = 0; i < rowA; ++i)
		for (int j = 0; j < colB; ++j)
			product[i][j] = 0;

	
	for (int i = 0; i < rowA; ++i)
		for (int j = 0; j < colB; ++j)
			for (int k = 0; k < colA; ++k) {
				product[i][j] += a[i][k] * b[k][j];
			}
	
	return product;

}


float ** transpose(float** a) {

	int c = arrayRow(a);// _msize(a) / sizeof(a[0]);
	int r = arrayCol(a);// _msize(a[0]) / sizeof(a[0][0]);


	//initial transpose
	float** trans = new float*[r];
	for (int i = 0; i < r; ++i)
		trans[i] = new float[c];



	// Finding transpose of matrix a[][] and storing it in array trans[][].
	for (int i = 0; i < c; ++i)
		for (int j = 0; j < r; ++j)
		{
			trans[j][i] = a[i][j];
		}
	return trans;
}

float ** eye(int n) {
	float** mat = new float*[n];
	for (int i = 0; i < n; i++) {
		mat[i] = new float[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)mat[i][j] =  1;
			else mat[i][j] = 0;
		}
	}
	return mat;
}
float** lambdaY(float lambda, int n) {
	return multi(eye(n), lambda);

}
//op 0: add 1:sub 2:inner product 
float** opArray(float** a, float** b, int op) {
	int rowA = arrayRow(a);
	int colA = arrayCol(a);
	int rowB = arrayRow(b);
	int colB = arrayCol(b);


	if (colA != colA || rowA != rowB)throw "Dimension not match!";

	float** mat = new float*[rowA];
	for (int i = 0; i < rowA; i++) {
		mat[i] = new float[colA];
	}

	for (int i = 0; i < rowA; i++) {
		for (int j = 0; j < colA; j++) {
			switch (op) {
			
			case 0:
				mat[i][j] = a[i][j] + b[i][j];
				break;
			case 1:
				mat[i][j] = a[i][j] - b[i][j];
				break;
			case 2:
				mat[i][j] = a[i][j] * b[i][j];
				break;
			default:
				mat[i][j] = a[i][j] + b[i][j];
			}

		}
	}
	return mat;

}
void printArray(float** mat) {

	int r = arrayRow(mat);// _msize(AT) / sizeof(AT[0]);
	int c = arrayCol(mat);// _msize(AT[0]) / sizeof(AT[0][0]);


	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
		{
			cout << " " << mat[i][j];
			if (j == c - 1)
				cout << endl << endl;
		}
}
//#include <boost/lambda/lambda.hpp>



float sum(float** mat) {
	float sum = 0;
	int r = arrayRow(mat);// _msize(AT) / sizeof(AT[0]);
	int c = arrayCol(mat);// _msize(AT[0]) / sizeof(AT[0][0]);


	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
		{
			sum += mat[i][j];
		}
	return sum;
}
float** square(float** inMat) {
	int r = arrayRow(inMat);// _msize(AT) / sizeof(AT[0]);
	int c = arrayCol(inMat);// _msize(AT[0]) / sizeof(AT[0][0]);
	float** mat = new float*[r];
	for (int i = 0; i < r; i++) {
		mat[i] = new float[c];
	}

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j)
		{
			mat[i][j] = inMat[i][j] * inMat[i][j];
		}
	}
	return mat;
}

