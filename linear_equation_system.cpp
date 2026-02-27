#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

void print_matrix(double** matrix, double* b, int n) {
	for (int i = 0; i < n; i++) {
		cout << "| ";
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << " | " << b[i] << " |" << endl;
	}
}

void set_problem(double** matrix, double* x, double* b, int n){
	if (n > 4) {
		for (int i = 0; i < n; i++) {
			x[i] = 1;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = 1 + rand() % 100;
			}
		}
		for (int i = 0; i < n; i++) {
			b[i] = 0;
			for (int j = 0; j < n; j++) {
				b[i] += matrix[i][j] * x[j];
			}
		}
	}
	else {
		cout << "Введите самостоятельно элементы вектора b:" << endl;
		for (int i = 0; i < n; i++) {
			cout << i + 1 << " элемент: ";
			cin >> b[i];
			cout << endl;
		}
		cout << "Введите элементы матрицы:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << "Элемент " << i + 1 << " строки " << j + 1 << " столбца: ";
				cin >> matrix[i][j];
				cout << endl;
			}
		}
		for (int i = 0; i < n; i++) {
			x[i] = 1;
		}
	}
}

double residual(double** matrix, double* x, double* b, int n) {
	double* r = new double[n];
	for (int i = 0; i < n; i++) {
		r[i] = -b[i];
		for (int j = 0; j < n; j++) {
			r[i] = matrix[i][j] * x[i];
		}
	}
	double max = abs(r[0]);
	for (int i = 0; i < n; i++) {
		if (max < abs(r[i])) {
			max = abs(r[i]);
		}
	}
	delete[] r;
	return max;
}

int main(int argc, char* argv) {

	return 0;
}