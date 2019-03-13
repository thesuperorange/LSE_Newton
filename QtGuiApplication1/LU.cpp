# include "systemfunction.h"
void LUdecomposition(float** A, float** L, float** U, int n) {
	int i = 0, j = 0, k = 0;
	float C;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) L[i][j] = 1;
			else if (i < j) L[i][j] = 0;
		}
		//cout << "i,j=" << i << " " << j << endl;
		if (i == 0) {
			for (j = 0; j < n; j++) {
				//	cout << "U=" << A[i][j] << endl;
				U[i][j] = A[i][j];
			}
		}
		else {
			for (j = 0; j < n; j++) {
				U[i][j] = A[i][j];
			}
			//cout << "U=" << A[i][j] << endl;
			for (k = 0; k < i; k++) {
				C = U[i][k] / U[k][k];
				//cout<<"C="<<U[i][k]<<"/"<<U[k][k] <<"="<<U<< endl;
				L[i][k] = C;
				for (j = 0; j < n; j++) {

					U[i][j] = U[i][j] - C * U[k][j];
				}
			}
		}

	}
}
float** Uinverse(float** U, int n) {
	float C = 0;
	//initial UI
	float** UI = new float*[n];
	for (int i = 0; i < n; i++) {
		UI[i] = new float[n];
	}
	for (int j = n - 1; j >= 0; j--) {
		for (int i = n - 1; i >= 0; i--) {
			if (i == j) UI[i][j] = 1;
			else UI[i][j] = 0;
		}
	}
	for (int j = n - 1; j >= 0; j--) {
		for (int i = j; i >= 0; i--) {
			if (i == j) {
				C = 1 / U[i][j];
				for (int k = j; k < n; k++) {
					UI[i][k] = UI[i][k] * C;
				}
			}
			else {
				for (int k = j; k < n; k++) {
					UI[i][k] = UI[i][k] - U[i][j] * UI[j][k];
				}
			}
		}
	}
	return UI;

}
float** Linverse(float** L, int n) {

	float C = 0;
	//initial LI
	float** LI = new float*[n];
	for (int i = 0; i < n; i++) {
		LI[i] = new float[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) LI[i][j] = 1;
			else LI[i][j] = 0;
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			for (int k = j; k >= 0; k--) {
				LI[i][k] = LI[i][k] - L[i][j] * LI[j][k];
			}
		}
	}
	return LI;
}


float** inverse(float** A) {
	if (arrayRow(A) != arrayCol(A))throw "[Error] row!=col, cannot calculate inverse.";
	int n = arrayRow(A);

	float** l = new float*[n];
	for (int i = 0; i < n; i++) {
		l[i] = new float[n];
	}

	float** u = new float*[n];
	for (int i = 0; i < n; i++) {
		u[i] = new float[n];
	}
	LUdecomposition(A, l, u, n);
	float** UI = Uinverse(u, n);
	float ** LI = Linverse(l, n);
	return multi(UI, LI);

}