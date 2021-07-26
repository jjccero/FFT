#include<iostream>
#include"fft.h"
using namespace std;


void show(complex** X, int u, int v) {
	for (int i = 0; i < u; i++) {
		for (int j = 0; j < v; j++) {
			printf("%8.4f", X[i][j].r);
			if (X[i][j].i >= 0)
				printf("+%-6.4fj ", X[i][j].i);
			else
				printf("%-7.4fj ", X[i][j].i);
		}
		cout << endl;
	}
}
void show(complex* X, int u) {
	for (int i = 0; i < u; i++) {
		printf("%8.4f", X[i].r);
		if (X[i].i >= 0)
			printf("+%-6.4fj ", X[i].i);
		else
			printf("%-7.4fj ", X[i].i);
		cout << endl;
	}

}
int main() {
	int u, v;
	/*
	cin >> u;
	complex* X = new complex[u], * x = new complex[u];
	for (int i = 0; i < u; i++) {
		double real;
		cin >> real;
		x[i] = complex(real, 0.0);
	}

	fft(x, X, u);
	cout << "fft:" << endl;
	show(X, u);
	fft(X, x, u, true);
	cout << "ifft:" << endl;
	show(x, u);
	*/

	/*
8 4
-1.0689  0.3252 -0.1022 -0.8649
 1.0933 -1.2141 -0.7697 -1.0891
-0.8095 -0.7549 -0.2414 -0.0301
 1.1093 -1.1135  0.3714  0.0326
-2.9443  1.3703  0.3192 -0.1649
-0.8637 -0.0068 -0.2256  0.5525
 1.4384 -1.7115  0.3129  0.6277
 0.0774  1.5326  1.1174  1.1006
	*/
	cin >> u >> v;
	complex** X = new complex * [u], ** x = new complex * [u];
	for (int i = 0; i < u; i++) {
		X[i] = new complex[v];
		x[i] = new complex[v];
	}

	for (int i = 0; i < u; i++) {
		for (int j = 0; j < v; j++) {
			double real;
			cin >> real;
			x[i][j] = complex(real, 0.0);
		}
	}

	fft2(x, X, u, v);
	cout << "fft:" << endl;
	show(X, u, v);
	fft2(X, x, u, v, true);
	cout << "ifft:" << endl;
	show(x, u, v);

	for (int i = 0; i < u; i++) {
		delete[] X[i];
		delete[] x[i];
	}

	delete[] X;
	delete[] x;
	return 0;
}
