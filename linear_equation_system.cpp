#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

//Стартовое окно
void hello(int& code) {
	cout << "0. Выход" << endl;
	cout << "1. Ввод данных - постановка задачи; запись в файл" << endl;
	cout << "2. Запись постановки задачи в файл" << endl;
	cout << "3. Получить постановку задачи из файла" << endl;
	cout << "4. Вывод системы на экран" << endl;
	cout << "5. Решение" << endl;
	cout << "6. Печать результата" << endl;
	cout << "Ваш выбор: ";
	cin >> code;
}

//Ввод данных
void set_problem(double** matrix, double* x, double* b, int& n, int& flag) {
	flag = 1;
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
		cout << "Заполни матрицу:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << "Введи элемент " << i + 1 << " строки " << j + 1 << " столбца: ";
				cin >> matrix[i][j];
			}
		}
		cout << "Вектор x будет единичным" << endl;
		for (int i = 0; i < n; i++) {
			x[i] = 1;
		}
		cout << "Вектор b получится в результате произведения матрицы на вектор x" << endl;
		for (int i = 0; i < n; i++) {
			b[i] = 0;
			for (int j = 0; j < n; j++) {
				b[i] += matrix[i][j] * x[j];
			}
		}
	}
}

//Вывод матрицы на консоль
void print_matrix(double** matrix, double* x, double* b, int n, int flag) {
	if (flag == 0) {
		cout << "Для начала введите данные" << endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		cout << "| ";
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << " | " << b[i] << " |" << endl;
	}
}

//Погрешность
double residual(double** matrix, double* x, double* b, int n) {
	double* r = new double[n];
	for (int i = 0; i < n; i++) {
		r[i] = -b[i];
		for (int j = 0; j < n; j++) {
			r[i] += matrix[i][j] * x[i];
		}
	}
	double max = abs(r[0]);
	for (int i = 1; i < n; i++) {
		if (max < abs(r[i])) {
			max = abs(r[i]);
		}
	}
	return max;
}

//Создание массивов
void create_mass(double**& matrix, double*& x, double*& b, int n) {
	matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n];
	}
	x = new double[n];
	b = new double[n];
}

//Удаление массивов
void delete_mass(double** matrix, double* x, double* b, int n) {
	if (matrix != nullptr) {
		for (int i = 0; i < n; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	if (x != nullptr) {
		delete[] x;
	}
	if (b!= nullptr) {
		delete[] b;
	}
}

//Запись постановки задачи в файл
void save_problem(double** matrix, double* x, double* b, int n, int& flag) {
	if (flag == 0) {
		cout << "Для начала введите данные" << endl;
		return;
	}
	ofstream fw;
	fw.open("C:\\matrix.txt");
	if (!fw) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	fw << n << endl;
	for (int i = 0; i < n; i++) {
		fw << "| ";
		for (int j = 0; j < n; j++) {
			fw << matrix[i][j] << " ";
		}
		fw << " | " << b[i] << " |" << endl;
	}
	for (int i = 0; i < n; i++) {
		fw << x[i] << " ";
	}
	fw << endl;
	fw.close();
}

//Считывание из файла постановки задачи
void get_problem(double**& matrix, double*& x, double*& b, int n) {
	ifstream fr;
	fr.open("C:\\matrix.txt");
	if (!fr) {
		cout << "Файл не удалось открыть" << endl;
		return;
	}
	char symbol;
	fr >> n >> ws;
	create_mass(matrix, x, b, n);
	for (int i = 0; i < n; i++) {
		fr >> symbol;
		for (int j = 0; j < n; j++) {
			fr >> matrix[i][j];
		}
		fr >> symbol >> b[i] >> symbol >> ws;
	}
	for (int i = 0; i < n; i++) {
		fr >> x[i];
	}
	fr.close();
}

int main(int argc, char* argv[]) {
	srand(time(0));
	setlocale(LC_ALL, "RUS");
	double** matrix = nullptr;
	double* x = nullptr;
	double* b = nullptr;
	int code = 0, n = 0, flag = 0;
	do {
		hello(code);
		switch (code) {
			case 0: break;
			case 1: 
				delete_mass(matrix, x, b, n);
				cout << "Введите размер матрицы: ";
				cin >> n;
				create_mass(matrix, x, b, n);
				set_problem(matrix, x, b, n, flag);
				break;
			case 2:
				save_problem(matrix, x, b, n, flag);
				break;
			case 3:
				delete_mass(matrix, x, b, n);
				get_problem(matrix, x, b, n);
				break;
			case 4:
				print_matrix(matrix, x, b, n, flag);
				break;
			default:
				if (cin.fail() || code > abs(5)) {
					cin.clear();
					cout << "Попробуйте снова" << endl;
					break;
				}
				break;
		}

	} while (code != 0);

	delete_mass(matrix, x, b, n);
	return 0;
}