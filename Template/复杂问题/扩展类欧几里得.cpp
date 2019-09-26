namespace _lo { //\sum_{x = 0} ^ {n} x ^ {k_1} {\left \lfloor \frac{ax + b}{c} \right \rfloor} ^ {k_2}
	static const int K = 10, P = 998244353; // e1+e2 <= K
	int inv[K + 2], C[K + 2][K + 2], B[K + 1]; // ²®Å¬ÀûÊý
	int cof[K + 1][K + 1], tmp[K + 1][K + 1], k;
	inline void add(int &a, int b) { if ((a += b) >= P) a -= P; }
	inline int mul(int a, int b) { return 1ll * a * b % P; }
	int reduce(int &a, int b) {
		int res = a / b;
		if ((a %= b) < 0) a += b, --res;
		return res;
	}

	void init() {
		inv[1] = 1; rep(i, 2, K+2) inv[i] = mul(P - P / i, inv[P % i]);
		rep(i, 0, K+2) {
			C[i][0] = 1;
			rep(j, 1, i+1) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
		rep(i, 0, K+1) {
			int sum = 0;
			rep(j, 0, i) add(sum, mul(C[i + 1][j], B[j]));
			B[i] = (1 + mul(P - sum, inv[i + 1])) % P;
		}
	}

	inline void calc(int x, bool o) {
		rep(i, 0, k) memcpy(tmp[i]+1, cof[i]+1, 4 * (k - i));
		for (int i = 1, u = x; i <= k; ++i, u = mul(u, x))
			rep(s, i, k+1) {
				int v = mul(C[s][i], u);
				rep(r, 0, k-s+1) add(cof[r + o * i][s - i], mul(v, tmp[r][s]));
			}
	}

	int run(int n, int a, int b, int c, int k1, int k2) {
		k = k1 + k2;
		int res = 0, sign = 1;
		if (k1 == 0) { res = 1; rep(i, 0, k2) res = mul(res, b / c); }
		rep(i, 0, k) memset(cof[i]+1, 0, 4 * (k - i));
		cof[k1][k2] = 1;
		while (1) {
			int cur = 0, x = reduce(a, c), y = (reduce(b, c) + P) % P;
			calc(x, 1); calc(y, 0);
			int l = ((ll)a * n + b) / c;
			rep(r, 0, k+1) {
				int sum = 0;
				for (int i = 1, u = n; i <= r + 1; ++i, u = mul(u, n))
					add(sum, mul(u, mul(C[r + 1][i], B[r + 1 - i])));
				sum = mul(sum, inv[r + 1]);
				for (int s = 0, u = sum; s <= k - r; ++s, u = mul(u, l)) add(cur, mul(u, cof[r][s]));
				cof[r][0] = 0;
			}
			add(res, mul(sign, cur));
			if (!a) break;
			rep(i, 0, k) memset(tmp[i], 0, 4 * (k - i));
			rep(s, 1, k+1)
				rep(i, 1, s+1) {
					int u = mul(C[s][i], i & 1 ? 1 : P - 1);
					rep(r, 0, k-s+1) add(tmp[r][s - i], mul(u, cof[r][s]));
				}
			rep(i, 0, k) memset(cof[i]+1, 0, 4 * (k - i));
			rep(r, 0, k)
				rep(i, 0, r+1) {
					int u = mul(C[r+1][i], mul(B[i], inv[r+1]));
					rep(s, 0, k-r) add(cof[s][r + 1 - i], mul(u, tmp[r][s]));
				}
			n = l; swap(a, c);
			b = -b - 1; sign = P - sign;
		}
		return res;
	}
}
