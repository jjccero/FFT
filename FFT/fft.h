#pragma once

struct complex {
	double r;
	double i;
	complex(double real = 0, double imag = 0);
	double abs();
	complex operator-(const complex& o);
	complex operator*(const complex& o);
	complex& operator/=(const double o);
	complex& operator+=(const complex& o);
};

complex get_weight(double k, double n);

void transform(complex* X, complex* weights, int bit_len);

int get_bit_length(int n);

int bit_inverse(int i, int bit_len);

void fft(complex* src, complex* dst, int n, bool inverse = false);

void fft2(complex** src, complex** dst, int u, int v, bool inverse = false);
