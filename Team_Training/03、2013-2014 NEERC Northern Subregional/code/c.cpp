#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 2020;

int n, m, l1, l2, r1, r2;
string s1, s2;
vi V;

namespace SAM {
	const int N = ::N << 1, M = 100;
	int par[N], l[N], ne[N][M], cnt[N], cur[N];
	int rt, last, L;
	vi rig[N];
	vector<pair<vi, int> > res;
	void add(int c) {
		int p = last, np = ++L;
		fill(ne[np], ne[np] + M, 0);
		l[np] = l[p] + 1;
		last = np;
		while(p && !ne[p][c]) ne[p][c] = np, p = par[p];
		if(!p) par[np] = rt;
		else {
			int q = ne[p][c];
			if(l[q] == l[p] + 1) par[np] = q;
			else {
				int nq = ++L;
				l[nq] = l[p] + 1;
				copy(ne[q], ne[q] + M, ne[nq]);
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && ne[p][c] == q) ne[p][c] = nq, p = par[p];
			}
		}
	}
	void ini() {
		rt = last = L = 1;
		fill(ne[rt], ne[rt] + M, 0);
		l[0] = -1;
	}
	void solve() {
		ini();
		rep(i, 0, sz(s1)) add(s1[i]);
		rep(i, 1, L + 1) ++cnt[l[i]];
		rep(i, 1, n + 1) cnt[i] += cnt[i - 1];
		rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
		rep(i, 1, L + 1) {
			int u = cur[i];
		//dd(u), dd(par[u]), de(l[u]);
		}
		int p = rt;
		rep(i, 0, sz(s1)) {
			p = ne[p][s1[i]];
			rig[p].pb(i);
		}
		per(i, 2, L + 1) {
			int u = cur[i];
			sort(all(rig[u]));
			rep(len, l[par[u]] + 1, l[u] + 1) {
				vi vec; int las = -1e9;
				for(auto ed : rig[u]) {
					if(ed - las >= len) vec.pb(ed - len + 1), las = ed;
				}
				res.pb(mp(vec, len));
			}
			int fa = par[u];
			if(sz(rig[fa]) < sz(rig[u])) rig[fa].swap(rig[u]);
			rig[fa].insert(rig[fa].end(), all(rig[u]));
			rig[u].clear();
		}
		return ;
		for(auto u : res) {
			auto v = u.fi;
			de(u.se);
			for(auto t : v) cout << t << " "; cout << endl;
		}
	}
}

inline int upd(int a, int b, int P) {
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}

inline int mul(int a, int b, int P) {
	return 1ll * a * b % P;
}
int kpow(int a, int b, int P) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a, P);
		a = mul(a, a, P);
		b >>= 1;
	}
	return res;
}

struct Dhash{
	static const int P = 1e9 + 7, Q = 1e9 + 9;
	int a, b;
	Dhash() {a = 0, b = 0;}
	Dhash(int a, int b) : a(a), b(b) {}
	inline Dhash operator + (const Dhash & c) const {return Dhash(upd(a, c.a, P), upd(b, c.b, Q));}
	inline Dhash operator - (const Dhash & c) const {return Dhash(upd(a, -c.a, P), upd(b, -c.b, Q));}
	inline Dhash operator * (const Dhash & c) const {return Dhash(mul(a, c.a, P), mul(b, c.b, Q));}
} B[N], h[N], inv[N], f[N];

Dhash get1(int l, int r) {
	if (l > r) return Dhash(0, 0);
	if (l == 0) return f[r];
	return (f[r] - f[l-1]) * inv[l];
}

Dhash get2(int l, int r) {
	if (l > r) return Dhash(0, 0);
	if (l == 0) return h[r];
	return (h[r] - h[l-1]) * inv[l];
}

int main() {
	freopen("curiosity.in", "r", stdin);
	freopen("curiosity.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	getline(cin, s1);
	getline(cin, s2);
	n = sz(s1); m = sz(s2);
	rep(i, 0, n) V.pb(s1[i]);
	rep(i, 0, m) V.pb(s2[i]);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 0, n) s1[i] = lower_bound(all(V), s1[i]) - V.begin(), s1[i]++; SAM::solve();
	rep(i, 0, m) s2[i] = lower_bound(all(V), s2[i]) - V.begin(), s2[i]++;
	B[0] = Dhash(1, 1); B[1] = Dhash(127, 233);
	rep(i, 2, max(n, m)+1) B[i] = B[i-1] * B[1];
	rep(i, 0, max(n, m)+1) inv[i] = Dhash(kpow(B[i].a, B[i].P - 2, B[i].P), kpow(B[i].b, B[i].Q - 2, B[i].Q));
	Dhash t;
	rep(i, 0, m) {
		h[i] = (i ? h[i-1] : Dhash(0, 0)) + B[i] * Dhash(s2[i], s2[i]);
	}
	t = Dhash(0, 0);
	rep(i, 0, n) {	
		//t = (t * B[1]) + Dhash(s1[i], s1[i]);
		//de(t.a);
		f[i] = (i ? f[i-1] : Dhash(0, 0)) + B[i] * Dhash(s1[i], s1[i]);
	}
	//de(mul(inv[3].a, B[3].a, B[3].P));
	//de(((f[3] - f[2]) * inv[3]).a);
	//de(mul(B[1].a, inv[1].a, B[1].P));
	vector<pair<vi, int> > res = SAM :: res;
	int ans = pw(30), ok = 0;
	for (auto u : res) {
		int d = (m - (n - u.se * sz(u.fi))), len = 0, pre = 0;
		//if (sz(u.fi) == 2 && u.se == 3) de(d);
		if (d < 0 || d % sz(u.fi)) continue;
		//de(d);
		d /= sz(u.fi);
		vi tmp;
		for (auto v : u.fi) if (!sz(tmp) || tmp.back() + u.se <= v) tmp.pb(v);
		Dhash t = get2(tmp[0], tmp[0] + d - 1), t2;
		for (auto v : tmp) {
			int x = v - pre;
			t2 = t2 + (get1(pre, v - 1) * B[len]);
			len += x;
			
			t2 = t2 + (t * B[len]);
			len += d;
			pre = v + u.se;

		}
		//if (u.se == 3) de(t2.a), de(h[m-1].a);
		t2 = t2 + (get1(pre, n - 1) * B[len]);
		//if (u.se == 1) for (auto v : tmp) dd(v);de(233); 
		if (t2.a == h[m-1].a && t2.b == h[m-1].b) {
			if (u.se + d < ans) {
				ok = 1;
				ans = u.se + d;
				l1 = tmp[0], r1 = tmp[0] + u.se - 1;
				l2 = tmp[0], r2 = tmp[0] + d - 1;
			}
		}
	}
	cout << "s/";
	rep(i, l1, r1+1) cout << char(V[s1[i]-1]);
	cout << "/";
	rep(i, l2, r2+1) cout << char(V[s2[i]-1]);
	cout << "/g";
	return 0; 
}
