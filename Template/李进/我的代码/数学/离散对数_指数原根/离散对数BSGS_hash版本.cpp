const int M = 65535, A = 2939;
ll rx[M + 10];
int ls[M + 10], LS = 0;
int ry[M + 10];
inline void ins(int x, int i) {
	int now = x & M;
	while (ls[now] == LS && rx[now] != x)
		now = now + A & M;
	ls[now] = LS;
	rx[now] = x;
	ry[now] = i;
	return;
}
inline int find(int x) {
	int now = x & M;
	while (ls[now] == LS) {
		if (rx[now] == x)
			return ry[now];
		now = now + A & M;
	}
	return -1;
}
ll bsgs(ll a, ll b, ll p) {
	LS++;
	register int i;
	a %= p;
	ll m = ceil(sqrt(p));
	ll tmp, ans = b % p;
	for (i = 0; i <= m; ++i) {
		ins(ans, i);
		ans = ans * a % p;
	}
	tmp = qm(a, m, p);
	ans = 1;
	for (i = 1; i <= m; ++i) {
		ans = ans * tmp % p;
		int j = find(ans);
		if (j != -1)
			return i * m - j;
	}
	return -1;
}

//LS 是记录计算次数，用于多次 hash，这样不用清空 hash 数组。