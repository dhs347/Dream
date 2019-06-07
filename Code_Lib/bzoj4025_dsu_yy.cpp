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

const int N = 101010;

int n, m, T, cnt;
vector<pii> vec[N << 2];
int pre[N], col[N];

pii find(int x, vector<pii> &ppre, vector<pii> &pcol) {
	if(x == pre[x]) return mp(x, 0);
	pii t = find(pre[x], ppre, pcol);
	t.se ^= col[x];
	ppre.pb(mp(x, pre[x]));
	pre[x] = t.fi;
	if(col[x] != t.se) {
		pcol.pb(mp(x, col[x]));
		col[x] = t.se;
	}
	return t;
}

#define ls rt << 1
#define rs ls | 1
void upd(int L, int R, int u, int v, int l, int r, int rt) {
	if(L <= l && r <= R) {
		vec[rt].pb(mp(u, v));
		return ;
	}
	int mid = l + r >> 1;
	if(L <= mid) upd(L, R, u, v, l, mid, ls);
	if(R > mid) upd(L, R, u, v, mid + 1, r, rs);
}
void dfs(int l, int r, int rt) {
	int pcnt = cnt;
	vector<pii> ppre, pcol;
	rep(i, 0, sz(vec[rt])) {
		int u = vec[rt][i].fi, v = vec[rt][i].se;
		pii fu = find(u, ppre, pcol), fv = find(v, ppre, pcol);
		if(fu.fi == fv.fi) {
			if(fu.se == fv.se) ++cnt;
		} else {
			ppre.pb(mp(fv.fi, pre[fv.fi])); pre[fv.fi] = fu.fi;
			if(fu.se == fv.se) col[fv.fi] = 1, pcol.pb(mp(fv.fi, 0));
		}
	}
	if(l == r) cout << (cnt ? "No" : "Yes") << endl;
	else {
		int mid = l + r >> 1;
		dfs(l, mid, ls);
		dfs(mid + 1, r, rs);
	}
	cnt = pcnt;
	per(i, 0, sz(ppre)) {
		pii t = ppre[i];
		pre[t.fi] = t.se;
	}
	per(i, 0, sz(pcol)) col[pcol[i].fi] = pcol[i].se;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> T;
	rep(i, 1, m + 1) {
		int u, v, st, ed;
		cin >> u >> v >> st >> ed;
		upd(st + 1, ed, u, v, 1, T, 1);
	}
	rep(i, 1, n + 1) pre[i] = i;
	dfs(1, T, 1);
	return 0;
}
