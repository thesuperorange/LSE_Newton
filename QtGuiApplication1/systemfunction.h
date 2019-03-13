#pragma once
# include "systemfunction.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;


//------matrix--------
int arraySize(float* a);
int arrayRow(float** a);
int arrayCol(float** a);
float** multi(float** a, float** b);
float ** transpose(float** a);
float ** eye(int n);
float** lambdaY(float lambda, int n);
float** opArray(float** a, float** b, int op);//op 0: add 1:sub 2:inner product 
void printArray(float** mat);
float sum(float** mat);
float** square(float** inMat);
//------FileReader--------
long countLine(string filename);
void readFile(string filename, long line_count, float* x, float** y);
//------LU --------
void LUdecomposition(float** A, float** L, float** U, int n);
float** Uinverse(float** U, int n);
float** Linverse(float** L, int n);
float** inverse(float** A);
//------LSE--------
float totalError(float** A, float** x, float** y);
void printFormula(float** Newton, int n);
string showFormula(float** Newton, int n);