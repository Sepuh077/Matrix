#pragma once
#include <iostream>

class Matrix
{
	double** a;
	int n, m;
	friend std::istream& operator>>(std::istream& in, Matrix& b);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& b);

public:
	Matrix(int n = 1, int m = 1);
	Matrix(int n, int m, double** a);
	Matrix(const Matrix& b);
	Matrix& operator=(const Matrix& b);
	bool operator==(const Matrix& b) const;
	bool operator!=(const Matrix& b) const;
	Matrix& operator+=(const Matrix& b);
	Matrix operator+(const Matrix& b) const;
	Matrix& operator-=(const Matrix& b);
	Matrix operator-(const Matrix& b) const;
	Matrix& operator*=(const Matrix& b);
	Matrix operator*(const Matrix& b) const;
	double operator()(int p, int q) const;
	double& operator()(int p, int q);
	void swap_col(int p, int q);
	void swap_row(int p, int q);
	int getCol();
	int getRow();
	~Matrix() {
		for (int i = 0; i < n; i++)
			delete[] a[i];
		delete[] a;
	}
};

