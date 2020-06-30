#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
	Matrix a, b;
	cin >> a >> b;
	//a(1, 1) = 90;
	try {
		a += b;
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	cout << a << endl;
	return 0;
}