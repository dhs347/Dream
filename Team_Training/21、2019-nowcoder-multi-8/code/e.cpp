#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010;

int n, m, ans;
pair<pii, pii> Q[N];
vi V;

int F(int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

int pre[N], h[N];

int find(int x) {
	while(x != pre[x]) x = pre[x];
	return x;
}
void join(int x, int y, vector<pii> &sp, vector<pii> &sh) {
	x = find(x), y = find(y);
	if(x == y) return ;
	if(h[x] > h[y]) swap(x, y);
	sp.pb(mp(x, pre[x]));
	pre[x] = y;
	if(h[x] == h[y]) {
		sh.pb(mp(y, h[y]));
		++h[y];
	}
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 3;
	vector<pii> nd[N];
	void upd(int u, int v, int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) {
			nd[rt].pb(mp(u, v));
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(u, v, L, R, l, mid, ls);
		if(R > mid) upd(u, v, L, R, mid + 1, r, rs);
	}
	void dfs(int l, int r, int rt) {
		vector<pii> sp, sh;
		for(auto t : nd[rt]) {
			int u = t.fi, v = t.se;
			join(u, v, sp, sh);
		}
		if(l == r || find(1) == find(n)) {
			if(find(1) == find(n)) {
				ans += V[r] - V[l - 1];
			}
		} else {
			int mid = l + r >> 1;
			dfs(l, mid, ls);
			dfs(mid + 1, r, rs);
		}
		per(i, 0, sz(sp)) {
			pre[sp[i].fi] = sp[i].se;
		}
		per(i, 0, sz(sh)) {
			h[sh[i].fi] = sh[i].se;
		}
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v, l, r; cin >> u >> v >> l >> r;
		Q[i] = mp(mp(u, v), mp(l, r));
		V.pb(l), V.pb(r + 1);
	}
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 1, m + 1) {
		int u = Q[i].fi.fi, v = Q[i].fi.se, l = Q[i].se.fi, r = Q[i].se.se;
		seg.upd(u, v, F(l), F(r + 1) - 1, 1, sz(V), 1);
	}
	rep(i, 1, n + 1) pre[i] = i;
	seg.dfs(1, sz(V), 1);
	cout << ans << endl;
	return 0;
}
