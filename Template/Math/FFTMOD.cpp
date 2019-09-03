const db PI = acos(-1);
const int M = 1 << 18 << 1;
int na, nb;
int a[M], b[M]; 

struct vir{
	db r, i;
	vir(db r = 0.0, db i = 0.0) : r(r), i(i){}
	inline vir operator +(const vir &c) {return vir(r + c.r, i + c.i);}
	inline vir operator -(const vir &c) {return vir(r - c.r, i - c.i);}
	inline vir operator *(const vir &c) {return vir(r * c.r - i * c.i, r * c.i + i * c.r);}
	inline vir operator !() const {return vir(r, -i);}
	void print() {printf("%lf %lf\n", r, i);}
};

struct FFTMOD{
	static const int M = 1 << 18 << 1;
	int N, L, MASK;
	vir w[M], A[M], B[M], C[M], D[M];

	void FFT(vir p[], int n) {
		for (int i = 1, j = 0; i < n - 1; ++i) {
			for (int s = n; j ^= s >>= 1, ~j & s;);
			if (i < j) swap(p[i], p[j]);
		}
		for (int d = 0; (1 << d) < n; ++d) {
			int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
			for (int i = 0; i < n; i += m2) {
				for (int j = 0; j < m; ++j) {
					vir &p1 = p[i + j + m], &p2 = p[i + j];
					vir t = w[rm * j] * p1;
					p1 = p2 - t, p2 = p2 + t;
				}
			}
		}
	}

	void doit(int *a, int *b, int na, int nb){
		for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, 0, na) a[i] = (a[i] % P + P) % P; rep(i, na, N) a[i] = 0;
		rep(i, 0, nb) b[i] = (b[i] % P + P) % P; rep(i, nb, N) b[i] = 0;
		L = 15;	MASK = (1<<L) - 1;
		rep(i, 0, N) w[i] = vir(cos(2 * i * PI / N), sin(2 * i * PI / N));
		rep(i, 0, N) {
			A[i] = vir(a[i] >> L, a[i] & MASK);
			B[i] = vir(b[i] >> L, b[i] & MASK);
		}
		mul(a);
	}

	void mul(int *a) {
		FFT(A, N), FFT(B, N);
		rep(i, 0, N) {
			int j = (N - i) % N;
			vir da = (A[i] - !A[j]) * vir(0, -0.5),
				db = (A[i] + !A[j]) * vir(0.5, 0),
				dc = (B[i] - !B[j]) * vir(0, -0.5),
				dd = (B[i] + !B[j]) * vir(0.5, 0);
			C[j] = da * dd + da * dc * vir(0, 1);
			D[j] = db * dd + db * dc * vir(0, 1);
		}
		FFT(C, N), FFT(D, N);
		rep(i, 0, N) {
			ll  da = (ll)(C[i].i / N + 0.5) % P,
				db = (ll)(C[i].r / N + 0.5) % P,
				dc = (ll)(D[i].i / N + 0.5) % P,
				dd = (ll)(D[i].r / N + 0.5) % P;
			a[i] = ((dd << (L * 2)) + ((db + dc) << L) + da) % P;
		}
	}
} fft;





