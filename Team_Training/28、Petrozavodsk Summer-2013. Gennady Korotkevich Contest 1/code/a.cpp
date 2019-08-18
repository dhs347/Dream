#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 202020;

int n, suf[N], mi[N << 2];
ll ans; int st, ed;
char s[N];
pair<pii, int> vec[N << 2], tmp[N << 2]; int cntn, cntm;

#define ls rt << 1
#define rs ls | 1
void up(int rt) {
	mi[rt] = mi[ls];
	if(suf[mi[rs]] < suf[mi[rt]]) mi[rt] = mi[rs];
}
void build(int l = 1, int r = n, int rt = 1) {
	if(l == r) {
		mi[rt] = l;
		return ;
	}
	int mid = l + r >> 1;
	build(l, mid, ls);
	build(mid + 1, r, rs);
	up(rt);
}

void qry(int L, int R, int l = 1, int r = n, int rt = 1) {
	if(L <= l && r <= R) {
		vec[++cntn] = mp(mp(l, r), rt);
		return ;
	}
	int mid = l + r >> 1;
	if(L <= mid) qry(L, R, l, mid, ls);
	if(R > mid) qry(L, R, mid + 1, r, rs);
}

void gao(int x) {
	cntm = 0;
	per(i, 1, cntn + 1) {
		int l = vec[i].fi.fi, r = vec[i].fi.se, rt = vec[i].se;
		if(suf[mi[rt]] >= x) {
			tmp[++cntm] = vec[i];
		} else {
			while(l < r) {
				int mid = l + r >> 1;
				if(suf[mi[rs]] >= x) {
					tmp[++cntm] = mp(mp(mid + 1, r), rs);
					r = mid;
					rt = ls;
				} else {
					l = mid + 1;
					rt = rs;
				}
			}
			break;
		}
	}
	reverse(tmp + 1, tmp + 1 + cntm);
}

int work(int x) {
	rep(i, 1, cntm + 1) {
		int l = tmp[i].fi.fi, r = tmp[i].fi.se, rt = tmp[i].se;
		if(suf[mi[rt]] == x) {
			while(1) {
				if(l == r) return l;
				int mid = l + r >> 1;
				if(suf[mi[ls]] == x) {
					r = mid;
					rt = ls;
				} else {
					l = mid + 1;
					rt = rs;
				}
			}
		}
	}
	return n + 1;
}

struct SAM {
	static const int N = ::N << 1, M = 2;
	int par[N], l[N], ne[N][M], cnt[N], cur[N], rig[N], sz[N];
	int rt, last, L;
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
	void init() {
		rt = last = L = 1;
		fill(ne[rt], ne[rt] + M, 0);
		l[0] = -1;
	}
	void solve() {
		rep(i, 1, L + 1) ++cnt[l[i]];
		rep(i, 1, L + 1) cnt[i] += cnt[i - 1];
		rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
		int p = rt;
		rep(i, 1, n + 1) {
			p = ne[p][s[i] - '0'];
			rig[p] = i;
			sz[p]++;
		}
		per(i, 1, L + 1) {
			int u = cur[i], fa = par[u];
			if(rig[u]) rig[fa] = rig[u];
			sz[fa] += sz[u];
		}
		rep(i, 2, L + 1) {
			int ed = rig[i], st = ed - l[i] + 1;
			cntn = 0; qry(st, ed);
			gao(suf[ed + 1]);
			int p = work(suf[ed + 1]);
			if(p <= ed) {
				ll res = (ed - p + 1) * 1ll * sz[i];
				if(res > ans) {
					ans = res;
					::st = p, ::ed = ed;
				}
			}
		}
	}
}sam;

int main() {
	freopen("abyss.in", "r", stdin);
	freopen("abyss.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> (s + 1);
	n = strlen(s + 1);
	sam.init();
	rep(i, 1, n + 1) sam.add(s[i] - '0');
	per(i, 1, n + 1) suf[i] = suf[i + 1] + (s[i] == '0' ? -1 : 1);
	build();
	sam.solve();
	cout << ans << endl;
	rep(i, st, ed + 1) cout << s[i]; cout << endl;
	return 0;
}
