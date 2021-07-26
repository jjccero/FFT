#include "fft.h"
#include<math.h>

double double_pi = 2 * acos(-1.0);

complex::complex(double real, double imag) :r(real), i(imag) {}
double complex::abs() {
	return sqrt(r * r + i * i);
}
complex complex::operator-(const complex& o) {
	return complex(r - o.r, i - o.i);
}
complex complex::operator*(const complex& o) {
	return complex(r * o.r - i * o.i, r * o.i + i * o.r);
}
complex& complex::operator/=(const double o) {
	r /= o;
	i /= o;
	return *this;
}
complex& complex::operator+=(const complex& o) {
	r += o.r;
	i += o.i;
	return *this;
}
complex get_weight(double k, double n) {
	double t = double_pi * k / n;
	return complex(cos(t), sin(t));
}

void transform(complex* X, complex* weights, int bit_len) {
	int n = 1 << bit_len;
	int dist = 1;
	for (int m = 1; m <= bit_len; m++) {
		for (int i = 0; i < n; i += 2 * dist) {
			for (int j = 0; j < dist; j++) {
				int k = i + j;
				int r = j << (bit_len - m);
				complex t = X[k + dist] * weights[r];
				X[k + dist] = X[k] - t;
				X[k] += t;
			}
		}
		dist <<= 1;
	}
}

int get_bit_length(int n) {
	for (int i = 0; i < 32; i++) {
		if ((1 << i) == n) return i;
	}
	return 0;
}

int bit_inverse(int i, int bit_len) {
	int inversed_i = 0;
	while (bit_len--) {
		inversed_i = (inversed_i << 1) + (i & 1);
		i /= 2;
	}
	return inversed_i;
}

void fft(complex* src, complex* dst, int n, bool inverse) {
	int bit_len = get_bit_length(n);
	double w = inverse ? 1.0 : -1.0;
	int weights_len = n / 2;
	complex* weights = new complex[weights_len];
	for (int i = 0; i < weights_len; i++)
		weights[i] = get_weight(w * i, n);
	for (int i = 0; i < n; i++)
		dst[i] = src[bit_inverse(i, bit_len)];
	transform(dst, weights, bit_len);
	delete[] weights;
	if (inverse)
		for (int i = 0; i < n; i++)
			dst[i] /= n;
}

void fft2(complex** src, complex** dst, int u, int v, bool inverse) {
	int u_bit_len = get_bit_length(u);
	int v_bit_len = get_bit_length(v);
	double w = inverse ? 1.0 : -1.0;

	int v_weights_len = v / 2;
	complex* v_weights = new complex[v_weights_len];
	for (int i = 0; i < v_weights_len; i++)
		v_weights[i] = get_weight(w * i, v);

	for (int x = 0; x < u; x++) {
		for (int y = 0; y < v; y++) {
			dst[x][y] = src[x][bit_inverse(y, v_bit_len)];
		}
		transform(dst[x], v_weights, v_bit_len);
	}
	delete[] v_weights;

	int u_weights_len = u / 2;
	complex* u_weights = new complex[u_weights_len];
	for (int i = 0; i < u_weights_len; i++)
		u_weights[i] = get_weight(w * i, u);
	complex* temps = new complex[u];
	for (int y = 0; y < v; y++) {
		for (int x = 0; x < u; x++)
			temps[x] = dst[bit_inverse(x, u_bit_len)][y];
		transform(temps, u_weights, u_bit_len);
		for (int x = 0; x < u; x++)
			dst[x][y] = temps[x];
	}
	delete[] temps;
	delete[] u_weights;

	if (inverse) {
		double uv = (double)u * v;
		for (int i = 0; i < u; i++) {
			for (int j = 0; j < v; j++) {
				dst[i][j] /= uv;
			}
		}
	}
}
