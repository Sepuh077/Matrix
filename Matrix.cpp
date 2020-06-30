#include "Matrix.h"

Matrix::Matrix(int n, int m) {
	this->n = n;
	this->m = m;
	a = new double* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new double[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			a[i][j] = 0;
	}
}
Matrix::Matrix(int n, int m, double** a) {
	this->n = n;
	this->m = m;
	this->a = new double* [n];
	for (int i = 0; i < n; i++) {
		this->a[i] = new double[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			this->a[i][j] = a[i][j];
	}
}
Matrix::Matrix(const Matrix& b) {
	n = b.n;
	m = b.m;
	a = new double* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new double[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			a[i][j] = b.a[i][j];
	}
}
Matrix& Matrix::operator=(const Matrix& b) {
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;
	n = b.n;
	m = b.m;
	a = new double* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new double[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			a[i][j] = b.a[i][j];
	}
	return *this;
}
bool Matrix::operator==(const Matrix& b) const {
	if (n != b.n || m != b.m)
		return 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] != b.a[i][j])
				return 0;
		}
	}
	return 1;
}
bool Matrix::operator!=(const Matrix& b) const {
	if (*this == b)
		return 0;
	return 1;
}
Matrix& Matrix::operator+=(const Matrix& b) {
	if (n != b.n || m != b.m) {
		throw("Can't add");
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			a[i][j] += b.a[i][j];
	}
	return *this;
}
Matrix Matrix::operator+(const Matrix& b) const {
	Matrix c(*this);
	return (c += b);
}
Matrix& Matrix::operator-=(const Matrix& b) {
	if (n != b.n || m != b.m) {
		throw("Can't subtract");
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			a[i][j] -= b.a[i][j];
	}
	return *this;
}
Matrix Matrix::operator-(const Matrix& b) const {
	Matrix c(*this);
	return (c -= b);
}
Matrix& Matrix::operator*=(const Matrix& b) {
	if (m != b.n) {
		throw("Can't multiply");
	}
	double** x = new double* [n];
	for (int i = 0; i < n; i++)
		x[i] = new double[m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			x[i][j] = a[i][j];
	}
	for (int i = 0; i < n; i++) {
		delete[] a[i];
		a[i] = new double[b.m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < b.m; j++) {
			double sum = 0;
			for (int p = 0; p < m; p++) {
				sum += (x[i][p] * b.a[p][j]);
			}
			a[i][j] = sum;
		}
	}
	for (int i = 0; i < n; i++)
		delete[] x[i];
	delete[] x;
	m = b.m;
	return *this;
}
Matrix Matrix::operator*(const Matrix& b) const {
	Matrix c(*this);
	return (c *= b);
}
double Matrix::operator()(int p, int q) const {
	if (p < 0)
		p = 0;
	if (p >= n)
		p = n - 1;
	if (q < 0)
		q = 0;
	if (q >= m)
		q = m - 1;
	return a[p][q];
}
double& Matrix::operator()(int p, int q) {
	if (p < 0)
		p = 0;
	if (p >= n)
		p = n - 1;
	if (q < 0)
		q = 0;
	if (q >= m)
		q = m - 1;
	return a[p][q];
}
void Matrix::swap_col(int p, int q) {
	if (p < 0)
		p = 0;
	if (p >= m)
		p = m - 1;
	if (q < 0)
		q = 0;
	if (q >= m)
		q = m - 1;
	if (p != q) {
		for (int i = 0; i < n; i++) {
			double x = a[i][p];
			a[i][p] = a[i][q];
			a[i][q] = x;
		}
	}
}
void Matrix::swap_row(int p, int q) {
	if (p < 0)
		p = 0;
	if (p >= n)
		p = n - 1;
	if (q < 0)
		q = 0;
	if (q >= n)
		q = n - 1;
	if (p != q) {
		for (int i = 0; i < m; i++) {
			double x = a[p][i];
			a[p][i] = a[q][i];
			a[q][i] = x;
		}
	}
}
int Matrix::getCol() {
	return m;
}
int Matrix::getRow() {
	return n;
}


std::istream& operator>>(std::istream& in, Matrix& b) {
	in >> b.n >> b.m;
	b.a = new double* [b.n];
	for (int i = 0; i < b.n; i++) {
		b.a[i] = new double[b.m];
	}
	for (int i = 0; i < b.n; ++i) {
		for (int j = 0; j < b.m; ++j) {
			in >> b.a[i][j];
		}
	}
	return in;
}
std::ostream& operator<<(std::ostream& out, const Matrix& b) {
	for (int i = 0; i < b.n; ++i) {
		for (int j = 0; j < b.m; ++j) {
			out << b.a[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}