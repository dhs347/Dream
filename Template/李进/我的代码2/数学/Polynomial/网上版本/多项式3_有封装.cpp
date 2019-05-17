#include <algorithm>
#include <cstring>
#include <cstdio>
#define MOD 998244353
#define GEN 3
typedef long long ll;
namespace polynomial
{
	inline int sum(int x, int y)
	{
		x += y;
		return x >= MOD ? x - MOD : x;
	}
	inline int sub(int x, int y)
	{
		x -= y;
		return x < 0 ? x + MOD : x;
	}
	inline int quick_pow(int a, int n)
	{
		int res = 1;
		while (n)
		{
			if (n & 1)
				res = (ll)res * a % MOD;
			a = (ll)a * a % MOD;
			n >>= 1;
		}
		return res;
	}
	int alpha[2][800005], poly_rev[800005], poly_ntt_lst = -1;
	inline void poly_ntt_init(int n)
	{
		if (poly_ntt_lst == n)
			return;
		poly_ntt_lst = n;
		alpha[0][0] = alpha[1][0] = 1;
		alpha[0][1] = quick_pow(GEN, (MOD - 1) / n);
		alpha[1][1] = quick_pow(alpha[0][1], MOD - 2);
		for (int i = 2; i <= n; i++)
		{
			for (int x = 0; x < 2; x++)
				alpha[x][i] = (ll)alpha[x][1] * alpha[x][i - 1] % MOD;
		}
		for (int i = 1, j = n >> 1; i + 1 < n; i++)
		{
			poly_rev[i] = j;
			int k = n >> 1;
			while (j >= k)
			{
				j -= k;
				k >>= 1;
			}
			j += k;
		}
	}
	inline void poly_ntt(int *arr, int n, bool f)
	{
		poly_ntt_init(n);
		for (int i = 1; i + 1 < n; i++)
		{
			if (i < poly_rev[i])
				std::swap(arr[i], arr[poly_rev[i]]);
		}
		for (int i = 1; i < n; i <<= 1)
		{
			for (int j = 0, off = n / (i << 1); j + i < n; j += i << 1)
			{
				for (int k = j, cur = 0; k < j + i; k++, cur += off)
				{
					int x = arr[k], y = (ll)arr[k + i] * alpha[f][cur] % MOD;
					arr[k] = (x + y >= MOD ? x + y - MOD : x + y);
					arr[k + i] = (x < y ? x - y + MOD : x - y);
				}
			}
		}
		if (f)
		{
			int x = quick_pow(n, MOD - 2);
			for (int i = 0; i < n; i++)
				arr[i] = (ll)arr[i] * x % MOD;
		}
	}
	inline void poly_mul(int *a, int *b, int n)
	{
		poly_ntt(a, n, false);
		poly_ntt(b, n, false);
		for (int i = 0; i < n; i++)
			a[i] = (ll)a[i] * b[i] % MOD;
		poly_ntt(a, n, true);
	}
	inline void poly_mul(int *a, int n, int *b, int m, int *res, int mx_len = -1)
	{
		static int A[800005], B[800005];
		if (-1 == mx_len)
			mx_len = n + m;
		n = std::min(n, mx_len);
		m = std::min(m, mx_len);
		int len = 1;
		while (len < n + m)
			len <<= 1;
		for (int i = 0; i < len; i++)
		{
			A[i] = i < n ? a[i] : 0;
			B[i] = i < m ? b[i] : 0;
		}
		poly_mul(A, B, len);
		memcpy(res, A, mx_len << 2);
	}
	inline void poly_inv(int *a, int *b, int n)
	{
		static int tmp[800005];
		b[0] = quick_pow(a[0], MOD - 2);
		for (int len = 2; len >> 1 < n; len <<= 1)
		{
			int lim = std::min(n, len);
			memcpy(tmp, a, lim << 2);
			memset(tmp + lim, 0, (len << 1) - lim << 2);
			memset(b + (len >> 1), 0, (len << 1) - (len >> 1) << 2);
			poly_ntt(tmp, len << 1, false);
			poly_ntt(b, len << 1, false);
			for (int i = 0; i < len << 1; i++)
				b[i] = (ll)b[i] * (2 - (ll)tmp[i] * b[i] % MOD + MOD) % MOD;
			poly_ntt(b, len << 1, true);
		}
	}
	inline void poly_der(int *a, int *b, int n)
	{
		for (int i = 0; i < n - 1; i++)
			b[i] = (ll)a[i + 1] * (i + 1) % MOD;
		b[n - 1] = 0;
	}
	inline void poly_int(int *a, int *b, int n)
	{
		for (int i = n - 1; i; i--)
			b[i] = (ll)a[i - 1] * quick_pow(i, MOD - 2) % MOD;
		b[0] = 0;
	}
	inline void poly_ln(int *a, int *b, int n)
	{
		static int tmp[800005];
		int len = 1;
		while (len >> 1 < n)
			len <<= 1;
		poly_inv(a, b, n);
		memset(b + (len >> 1), 0, (len >> 1) << 2);
		poly_der(a, tmp, n);
		memset(tmp + n - 1, 0, (len - n + 1) << 2);
		poly_mul(tmp, b, len);
		poly_int(tmp, b, n);
	}
	inline void poly_exp(int *a, int *b, int n)
	{
		static int tmp[800005];
		b[0] = 1;
		for (int len = 2; len >> 1 < n; len <<= 1)
		{
			memset(b + (len >> 1), 0, (len << 1) - (len >> 1) << 2);
			poly_ln(b, tmp, len);
			for (int i = 0; i < len; i++)
				tmp[i] = sub(i < n ? a[i] : 0, tmp[i]);
			tmp[0] = sum(tmp[0], 1);
			memset(tmp + len, 0, len << 2);
			poly_mul(b, tmp, len << 1);
		}
	}
	inline void poly_pow(int *f, int *g, int n, int m)
	{
		int pos = 0;
		while (pos < n && !f[pos])
			pos++;
		if ((ll)pos * m >= n)
		{
			memset(g, 0, n << 2);
			return;
		}
		for (int i = pos; i < n; i++)
			f[i - pos] = f[i];
		int coef = f[0], x = quick_pow(coef, MOD - 2);
		for (int i = 0; i < n - pos; i++)
			f[i] = (ll)f[i] * x % MOD;
		int len = 1, rem = n - pos * m;
		while (len < rem)
			len <<= 1;
		memset(f + rem, 0, len - rem << 2);
		poly_ln(f, g, len);
		for (int i = 0; i < len; i++)
			g[i] = (ll)g[i] * m % MOD;
		poly_exp(g, f, len);
		coef = quick_pow(coef, m);
		for (int i = 0; i < pos * m; i++)
			g[i] = 0;
		for (int i = 0; i < rem; i++)
			g[i + pos * m] = (ll)f[i] * coef % MOD;
	}
	inline void poly_sqrt(int *a, int *b, int n)
	{
		static int tmp[800005], t[800005];
		b[0] = 1;
		while (b[0] * b[0] < a[0])
			b[0]++;
		for (int len = 2; (len >> 1) < n; len <<= 1)
		{
			int lim = std::min(n, len);
			memcpy(t, a, lim << 2);
			memset(t + lim, 0, (len << 1) - lim << 2);
			memset(b + (len >> 1), 0, (len << 1) - (len >> 1) << 2);
			poly_inv(b, tmp, len);
			memset(tmp + len, 0, len << 2);
			poly_ntt(t, len << 1, false);
			poly_ntt(b, len << 1, false);
			poly_ntt(tmp, len << 1, false);
			for (int i = 0; i < len << 1; i++)
				b[i] = (ll)sum(b[i], (ll)tmp[i] * t[i] % MOD) * (MOD + 1) / 2 % MOD;
			poly_ntt(b, len << 1, true);
			memset(b + len, 0, len << 2);
		}
	}
	inline void poly_div(int *a, int *b, int *d, int *r, int n, int m)
	{
		if (n < m)
		{
			memcpy(r, a, n << 2);
			memset(r + n, 0, m - n << 2);
			return;
		}
		static int ar[800005], br[800005], tmp[800005];
		int len = 1, t = n - m + 1;
		while (len < t << 1)
			len <<= 1;
		std::reverse_copy(b, b + m, tmp);
		if (m < t)
			memset(tmp + m, 0, t - m << 2);
		poly_inv(tmp, br, t);
		memset(br + t, 0, len - t << 2);
		std::reverse_copy(a + m - 1, a + n, ar);
		memset(ar + t, 0, len - t << 2);
		poly_mul(ar, br, len);
		std::reverse(ar, ar + t);
		memcpy(d, ar, len << 2);
		memcpy(br, b, m << 2);
		poly_mul(br, m, ar, t, tmp);
		for (int i = 0; i < m; i++)
			r[i] = sub(a[i], tmp[i]);
	}
	namespace poly_eval_itpl_func
	{
		int func[21][800005], mod_res[21][200005], coef[800005], itpl_res[21][800005];
	}
	inline void poly_eval_itpl_init(int dep, int *pos, int l, int r)
	{
		using namespace poly_eval_itpl_func;
		if (l == r)
		{
			func[dep][l << 1] = MOD - pos[l] % MOD;
			func[dep][l << 1 | 1] = 1;
			return;
		}
		int m = l + r >> 1;
		poly_eval_itpl_init(dep + 1, pos, l, m);
		poly_eval_itpl_init(dep + 1, pos, m + 1, r);
		poly_mul(func[dep + 1] + (l << 1), m - l + 2,
				 func[dep + 1] + (m + 1 << 1), r - (m + 1) + 2,
				 func[dep] + (l << 1), r - l + 2);
	}
	void poly_eval_recurse(int dep, int *a, int n, int l, int r, int *res)
	{
		using namespace poly_eval_itpl_func;
		static int tmp[800005];
		poly_div(a, func[dep] + (l << 1), tmp, mod_res[dep] + l, n, r - l + 2);
		if (l == r)
		{
			res[l] = mod_res[dep][l];
			return;
		}
		int m = l + r >> 1;
		poly_eval_recurse(dep + 1, mod_res[dep] + l, r - l + 1, l, m, res);
		poly_eval_recurse(dep + 1, mod_res[dep] + l, r - l + 1, m + 1, r, res);
	}
	inline void poly_eval(int *a, int *pos, int *res, int n, int m)
	{
		poly_eval_itpl_init(0, pos, 0, m - 1);
		poly_eval_recurse(0, a, n, 0, m - 1, res);
	}
	inline void poly_itpl_recurse(int dep, int l, int r)
	{
		using namespace poly_eval_itpl_func;
		if (l == r)
		{
			itpl_res[dep][l << 2] = coef[l];
			return;
		}
		int m = l + r >> 1;
		poly_itpl_recurse(dep + 1, l, m);
		poly_itpl_recurse(dep + 1, m + 1, r);
		poly_mul(itpl_res[dep + 1] + (l << 2), m - l + 1,
				 func[dep + 1] + (m + 1 << 1), r - m + 1,
				 itpl_res[dep + 1] + (l << 2));
		poly_mul(itpl_res[dep + 1] + (m + 1 << 2), r - m,
				 func[dep + 1] + (l << 1), m - l + 2,
				 itpl_res[dep + 1] + (m + 1 << 2));
		for (int i = 0; i <= r - l + 1; i++)
			itpl_res[dep][(l << 2) + i] = sum(itpl_res[dep + 1][(l << 2) + i], itpl_res[dep + 1][(m + 1 << 2) + i]);
	}
	inline void poly_itpl(int *pos, int *val, int n, int *a)
	{
		using namespace poly_eval_itpl_func;
		poly_eval_itpl_init(0, pos, 0, n - 1);
		static int tmp[800005], der[800005];
		memcpy(tmp, func[0], sizeof(func[0]));
		poly_der(tmp, der, n + 1);
		poly_eval_recurse(0, der, n, 0, n - 1, coef);
		for (int i = 0; i < n; i++)
			coef[i] = (ll)val[i] * quick_pow(coef[i], MOD - 2) % MOD;
		poly_itpl_recurse(0, 0, n - 1);
		memcpy(a, itpl_res[0], n << 2);
	}
}
using namespace polynomial;

int a[5000005], b[5000005], c[5000005], d[5000005], e[5000005], f[5000005], g[5000005], h[5000005], res[5000005];
int main()
{
	// freopen("cogs-2189.in", "r", stdin);
	freopen("polynomial.in", "r", stdin);
	freopen("polynomial.out", "wt", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	int len = 1;
	while (len >> 1 < n)
		len <<= 1;
	poly_sqrt(a, b, len);
	poly_inv(b, c, len);
	poly_int(c, d, len);
	poly_exp(d, e, len);
	poly_inv(e, f, len);
	f[0] = sum(f[0], 1);
	poly_ln(f, g, len);
	g[0] = sum(g[0], 1);
	poly_pow(g, h, len, k);
	poly_der(h, res, n);
	for (int i = 0; i < n; i++)
		printf("%d%c", res[i], " \n"[i + 1 == n]);
	return 0;
}
