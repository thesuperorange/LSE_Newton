# include "systemfunction.h"

float totalError(float** A, float** x, float** y)
{
	
	float** sqrA = square(opArray(multi(A, x), y, 1));
	return sum(sqrA);
}

string showFormula(float** Newton, int n) {

	string fitline =  "Fitting line: ";
	for (int i = n - 1; i >= 0; i--) {
		if (i != n - 1 && Newton[i][0] > 0)fitline = fitline+ "+";

		
			fitline = fitline + to_string(Newton[i][0]);

		if (i != 0) {
			
			fitline = fitline + " x^"+to_string(i);
			

		}
	}
	return fitline;
}
void printFormula(float** Newton, int n) {
	cout << endl << "Fitting line: ";
	for (int i = n - 1; i >= 0; i--) {
		if (i != n - 1 && Newton[i][0] > 0)cout << "+";
		cout << Newton[i][0];

		if (i != 0) {
			cout << " x^" << i;

		}
	}
}