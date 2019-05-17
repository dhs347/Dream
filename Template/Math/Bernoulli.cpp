// desc : 0^k + 1^k + 2^k + .. + (n-1)^k
// time-ini : O(n^2)
// time-cal : k + log
namespace Bernoulli {
	const int N = 1000;
	int C[N][N], B[N];
	void ini() {
		rep(i, 0, N) C[i][0] = 1;
		rep(i, 0, N) rep(j, 1, i + 1) C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
		B[0] = 1;
		rep(i, 1, N) {
			B[i] = 0;
			rep(j, 0, i) B[i] = add(B[i], MOD - mul(C[i + 1][j], B[j]));
			B[i] = mul(B[i], qpow(C[i + 1][i], MOD - 2)) % MOD;
		}
	}
	int cal(int n, int k) { 
		int sum = 0;
		rep(i, 0, k + 1) sum = add(sum, mul(C[k + 1][i], mul(B[i], qpow(n, k + 1 - i))));
		return mul(sum, qpow(k + 1, MOD - 2));
	}
};

