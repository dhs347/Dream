#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 27000 + 5;
int B;

struct FastIO {
	static const int S = 1310720;
	int wpos;
	char wbuf[S];
	bool ed;
	FastIO() : wpos(0), ed(0) {}
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
			if(!~c) return ed = 1;
			c = xchar();
		}
		if(c == '-') s = -1, c = xchar();
		for( ; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x * s;
	}
	inline void wll(ll x) {
		if(x < 0) wchar('-'), x = -x;
		char s[48];
		int n = 0;
		while(x || !n) s[n++] = '0' + x % 10, x /= 10;
		while(n--) wchar(s[n]);
	}
	inline void wchar(int x) {
		if(wpos == S) fwrite(wbuf, 0, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	~FastIO() {
		if(wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
}io;

int n, m, k, a[N], L[N], R[N];
ll res, ans[N];
vi vec;
struct Node {
	int l, r, ind;
	bool operator < (const Node &c) const {
		if(l / B != c.l / B) return l / B < c.l / B;
		return (r < c.r) ^ ((l / B) & 1);
	}
}nd[N];
inline int F(int x) {
	return lower_bound(all(vec), x) - vec.begin() + 1;
}
#define lb(x) ((x)&-(x))
struct Fenwick {
	int n; int a[N];
	void ini(int _n) {
		n = _n; fill_n(a + 1, n, 0);
	}
	inline void upd(int p, int c) {
		for( ; p <= n; p += lb(p)) a[p] += c;
	}
	inline int _qry(int p) {
		int r = 0;
		for( ; p; p ^= lb(p)) r += a[p];
		return r;
	}
	inline int qry(int l, int r) {
		if(l > r) return 0;
		if(r > n) r = n;
		if(l < 1) l = 1;
		return _qry(r) - _qry(l - 1);
	}
}fw;
inline void upd(int p, int c) {
	int x = a[p];
	if(c == -1) fw.upd(F(x), c);
	int l = L[p], r = R[p];
	res += c * fw.qry(l, r);
	if(c == 1) fw.upd(F(x), c);
}
int main() {
	n = io.xint(); m = io.xint(); k = io.xint();
	B = sqrt(n); vec.clear(); res = 0;
	rep(i, 1, n + 1) a[i] = io.xint(), vec.pb(a[i]);
	sort(all(vec));
	vec.erase(unique(all(vec)), vec.end());
	fw.ini(sz(vec));
	rep(i, 1, m + 1) nd[i].l = io.xint(), nd[i].r = io.xint(), nd[i].ind = i;
	sort(nd + 1, nd + 1 + m);
	rep(i, 1, n + 1) {
		int x = a[i];
		L[i] = F(x - k);
		R[i] = upper_bound(all(vec), x + k) - vec.begin();
	}
	int l = 1, r = 0;
	rep(i, 1, m + 1) {
		while(l < nd[i].l) upd(l++, -1);
		while(l > nd[i].l) upd(--l, 1);
		while(r < nd[i].r) upd(++r, 1);
		while(r > nd[i].r) upd(r--, -1);
		ans[nd[i].ind] = res;
	}
	rep(i, 1, m + 1) io.wll(ans[i]), io.wchar('\n');
	return 0;
}
