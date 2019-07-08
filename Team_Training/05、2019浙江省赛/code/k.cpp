#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 2e6 + 7;

int len, n, st, ed;
int pa[N << 2];
char a[N], b[N], s[N << 1];

struct IO {
	static const int S = 1310720;
	int wpos;
	char wbuf[S];
	IO() : wpos(0) {}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if(pos == len) pos = 0, len = fread(buf, 1, S, stdin);
		if(pos == len) return -1;
		return buf[pos++];
	}
	inline int xint() {
		int c = xchar(), x = 0, s = 1;
		while(c <= 32) {
			c = xchar();
		}
		if(c == '-') s = -1, c = xchar();
		for(; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x * s;
	}
	inline void xstring(char *s) {
		int c = xchar();
		while(c <= 32) c = xchar();
		for(; c > 32; c = xchar()) *s++ = c;
		*s = 0;
	}
}io;

inline void man(char *s, int n, int *pa) {
	pa[0] = 1;
	for(int i = 1, j = 0; i < (n << 1) - 1; ++i) if(i & 1) {
		int p = i >> 1, q = i - p, r = ((j + 1) >> 1) + pa[j] - 1;
		pa[i] = r < q ? 0 : min(r - q + 1, pa[(j << 1) - i]);
		while(0 <= p - pa[i] && q + pa[i] < n && s[p - pa[i]] == s[q + pa[i]]) pa[i]++;
		if(q + pa[i] - 1 > r) j = i;
	}
}
inline int calc1(int x) {
	return x < 0 ? 0 : x / 2 + 1;
}
inline int calc1(int l1, int r1, int l2, int r2) {
	int l = max(l1, l2);
	int r = min(r1, r2);
	return l > r ? 0 : calc1(r) - calc1(l - 1);
}
inline int calc2(int x) {
	return x <= 0 ? 0 : (x - 1) / 2 + 1;
}
inline int calc2(int l1, int r1, int l2, int r2) {
	int l = max(l1, l2);
	int r = min(r1, r2);
	return l > r ? 0 : calc2(r) - calc2(l - 1);
}
inline void solve() {
	io.xstring(a);
	io.xstring(b);
	//scanf("%s%s", a, b);
	len = strlen(a);
	n = 0;
	rep(i, 0, len) s[n++] = a[i], s[n++] = b[i];
	man(s, n, pa);
	st = 0;
	for(int i = 1; i < n; i += 2) {
		if(s[i] == s[i - 1]) st += 2;
		else break;
	}
	ed = n - 1;
	for(int i = n - 2; i >= 0; i -= 2) {
		if(s[i] == s[i + 1]) ed -= 2;
		else break;
	}
	ll ans = 0;
	rep(i, 0, n - 1) {
		int pp = pa[i << 1 | 1];
		ans += min(calc1(i - pp + 1, i, 0, st), calc2(i + 1, i + pp, ed, n - 1));
	}
	printf("%lld\n", ans);
}

int main() {
	int T = io.xint();
	while(T--) solve();
	return 0;
}
