ll solve() {
	ll ans = 0;
	for (int i = 1; i <= k+1; ++i) {
		ans += c[k+1][i] * b[k+1 -i] % MOD * m[i] % MOD;
		ans %= MOD;
	}
	ans = ans * Inv[k+1] % MOD;
	return ans;
}
int main() {
//首先 递推求逆元求出 Inv 数组。
//其次 初始化组合数
//初始化伯努利数
	memset(b, 0, sizeof(b));
	b[0] = 1;
	for (i = 1; i < N; ++i) {
		for (j = 0; j < i; ++j) {
			b[i] += c[i+1][j] * b[j];
			b[i] %= MOD;
		}
		b[i] *= -1 * Inv[i + 1];
		b[i] %= MOD;
		b[i] = (b[i] + MOD) % MOD;
	}
	scanf(”%d”,&t);
	while (t--) {
		scanf(”%lld %d”,&n,&k);
		n %= MOD;
//初始化幂数组
		m[0] = 1;
		for (i = 1; i <= N; ++i)
			m[i] = m[i-1] * (n+1) % MOD;
		ans = solve();
		printf(”%lld\n”, ans);
	}
	return 0;
}
