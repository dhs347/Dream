const int N = 404005;
const int G = 3;
const ll mod = 1004535809;
ll w[2][N];
ll d;
ll la, lb, i, t, m, inv;
char s[400000];
ll a[400000];
ll b[400000];
ll pow(ll x, ll y, ll p) {
	static ll res;
	res = 1;
	while (y) {
		if (y & 1) res = res * x % p;
		x = x * x % p, y >>= 1;
	}
	return res;
}
inline int get_inv(ll x, ll mod) {
	return pow(x, mod - 2, mod);
}
inline void pre() {
	int i, t;
	w[0][0] = w[0][d] = 1;
	t = pow(G, (mod - 1) / d, mod);
	for (i = 1; i < d; ++i) w[0][i] = 1ll * w[0][i - 1] * t % mod;
	for (i = 0; i <= d; ++i) w[1][i] = w[0][d - i];
}
void NTT(ll *x, ll k, ll v) {
	int i, j, l, tmp;
	for (i = j = 0; i < k; ++i) {
		if (i > j) swap(x[i], x[j]);
		for (l = k >> 1; (j ^= l) < l; l >>= 1);
	}
	for (i = 2; i <= k; i <<= 1)
		for (j = 0; j < k; j += i)
			for (l = 0; l < i >> 1; ++l) {
				tmp = 1ll * x[j + l + (i >> 1)] * w[v][k / i * l] % mod;
				x[j + l + (i >> 1)] = (1ll * x[j + l] - tmp + mod) % mod;
				x[j + l] = (1ll * x[j + l] + tmp) % mod;
			}
}
int main() {
	scanf("%s", s);
	la = strlen(s);
	memset(a, 0, sizeof(a));
	for (i = 0; i < la; ++i) a[i] = s[la - 1 - i] - 48;
	scanf("%s", s);
	lb = strlen(s);
	memset(b, 0, sizeof(b));
	for (i = 0; i < lb; ++i) b[i] = s[lb - 1 - i] - 48;
	m = max(la, lb);
	for (d = 1; d <= m << 1; d <<= 1);
	pre();
	NTT(a, d, 0);
	NTT(b, d, 0);
	for (i = 0; i < d; ++i) a[i] = 1ll * a[i] * b[i] % mod;
	NTT(a, d, 1);
	for (inv = get_inv(d, mod), i = 0; i < d; ++i)
		a[i] = 1ll * a[i] * inv % mod;
	t = 0;
	for (i = 0; i < d; ++i) {
		a[i+1] += a[i] / 10;
		a[i] %= 10;
		if (a[i] != 0) t = i;
	}
	for (i = t; i >= 0; --i) printf(”%lld”, a[i]);
	printf(”\n”);
	return 0;
}