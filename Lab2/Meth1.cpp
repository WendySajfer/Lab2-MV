#include <iostream>
#include "windows.h"
#include <vector>
#include "string"
#include <cmath>

using namespace std;

class Matrix {
private:
	vector<vector<double>> matrix;
	vector<int> width_form;
	int m = 0, n = 0;

	void Format() {
		width_form.clear();
		int width, buf_width, width_null;
		string str_width;
		width = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				str_width = to_string(matrix[j][i]);
				for (int i = str_width.size() - 1; i >= 0; i--) {
					if (str_width[i] == '0' || str_width[i] == ',') {
						str_width.erase(i);
					}
					else break;
				}
				buf_width = str_width.size();
				if (width < buf_width) width = buf_width;
			}
			width_form.push_back(width);
		}
	}
	void Size() {
		m = matrix.size();
		n = matrix[0].size();
		for (int i = 1; i < m; i++) {
			if (matrix[i].size() != n) {
				n = 0;
				break;
			}
		}
	}
public:
	void Input_Matrix(int m, int n)
	{
		double number;
		vector<double> str_matrix;
		cout << "Enter the [" << m << "," << n << "] matrix:" << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cin >> number;
				str_matrix.push_back(number);
			}
			matrix.push_back(str_matrix);
			str_matrix.clear();
		}
	}
	void Output_Matrix() { 
		Size();
		if (n == 0 || m == 0) {
			return;
		}
		Format();
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout.width(width_form[j]);
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void Output_SLAU() {
		Size();
		if (n == 0 || m == 0) {
			return;
		}
		Format();
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout.width(width_form[j]);
				cout << matrix[i][j] << " ";
				if (j == n - 2) cout << "| ";
			}
			cout << endl;
		}
		cout << endl;
	}
	vector<vector<double>> get_Matrix() {
		return matrix;
	}
	void set_SLAU(vector<vector<double>> slau) {
		matrix = slau;
	}
};

class SLAU {
private:
	vector<vector<double>> matrix_slau;
	vector<double> X;
	Matrix M;
	void Accur_str(int str_index) {
		double buf;
		vector<double> str_slau = matrix_slau[str_index];
		for (int i = 0; i < str_slau.size(); i++) {
			buf = abs(str_slau[i]);
			if (buf != 0) {
				if (fmod(buf, 0.001) < 1) {
					str_slau[i] = round(str_slau[i] * 1000) / 1000;
				}
			}
		}
		matrix_slau[str_index] = str_slau;
	}
	double Accur(double n) {
		double buf = abs(n);
		if (buf != 0) {
			if (fmod(buf, 0.001) < 1) {
				n = round(n * 1000) / 1000;
			}
		}
		return n;
	}
	void Output_SLAU() {
		M.set_SLAU(matrix_slau);
		M.Output_SLAU();
	}
	void Sub_Str(int str1_index, int str2_index, int null_index) {
		double diff;
		vector<double> str1_slau = matrix_slau[str1_index];
		vector<double> str2_slau = matrix_slau[str2_index];

		diff = str2_slau[null_index] / str1_slau[null_index];
		for (int i = 0; i < str1_slau.size(); i++) {
			str2_slau[i] -= (str1_slau[i] * diff);
		}
		matrix_slau[str2_index] = str2_slau;
		Accur_str(str2_index);
	}
	void X_Record(int number) {
		double buf_x = 0;
		for (int i = 0; i < matrix_slau.size(); i++) {
			if (i != number) {
				if (abs(matrix_slau[number][i]) > 0.001) {
					buf_x += (matrix_slau[number][i] * X[matrix_slau.size() - i - 1]);
				}
			}
		}
		buf_x -= matrix_slau[number][matrix_slau.size()];
		buf_x /= -(matrix_slau[number][number]);
		buf_x = Accur(buf_x);
		X.push_back(buf_x);
	}
public:
	void Input_SLAU(vector<vector<double>> matrix_A, vector<vector<double>> matrix_B) {
		if (matrix_A.size() != matrix_B.size() || matrix_B[0].size() != 1) {
			return;
		}
		matrix_slau = matrix_A;
		for (int i = 0; i < matrix_A.size(); i++) {
			matrix_slau[i].push_back(matrix_B[i][0]);
		}
	}
	void Decision() {
		for (int i = 1; i < matrix_slau[0].size() - 1; i++) {
			for (int j = 0; j < i; j++) {
				if (matrix_slau[i][j] != 0) {
					Sub_Str(j, i, j);
					Output_SLAU();
				}
			}
			
		}
	}
	void Rezult() {
		for (int i = matrix_slau.size() - 1; i >= 0; i--) {
			X_Record(i);
		}
		cout << "Answer: ";
		for (int i = 0; i < X.size(); i++) {
			cout << "x" << i+1 << " = " << X[X.size() - 1 - i] << ", ";
 		}
		cout << endl;
	}
};

class Task {
private:
	Matrix M;
	Matrix M1;
	SLAU Slau;
	int m, n;
	void Create_SLAU() {
		m = 4;
		n = 4;
		M.Input_Matrix(m, n);
		m = 4;
		n = 1;
		M1.Input_Matrix(m, n);
	}
public:
	void SLAU_Task() {
		Create_SLAU();
		M.Output_Matrix();
		M1.Output_Matrix();
		Slau.Input_SLAU(M.get_Matrix(), M1.get_Matrix());
		Slau.Decision();
		Slau.Rezult();
	}
};

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	int ans, exit = 1;
	while (exit == 1) {
		Task T;
		cout << "1.SLAU" << endl << "2.Exit" << endl << "Choose a way:" << endl;
		cin >> ans;
		switch (ans)
		{
		case 1:
			T.SLAU_Task();
			break;
		case 2:
			exit = 0;
			break;
		default:
			cout << "This task does not exist" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}

/*
1.7 -1.8 1.9 -57.4
1.1 -4.3 1.5 -1.7
1.2 1.4 1.6 1.8
7.1 -1.3 -4.1 5.2
10
19
20
10

*/