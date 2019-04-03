#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 50505;

int n, m, key, rt;
int t[N];
vi g[N];

namespace MoOnTree {

	const int N = ::N, SZ = sqrt(N), M = 17;

	int cd;
	int dep[N], pre[N][M], st[N], ed[N], dfn[N << 1], B[N << 1], cnt[N];
	struct Node {
		int l, r, id, lca;
		Node(int id, int l, int r, int lca = 0) : id(id), l(l), r(r), lca(lca) {}
		bool operator < (const Node &c) const {
			if(B[l] != B[c.l]) return B[l] < B[c.l];
			return (r < c.r) ^ (B[l] & 1);
		}
	};
	vector<Node> nds;

	void dfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		pre[u][0] = fa;
		for(int i = 1; i < M && pre[u][i - 1]; ++i) pre[u][i] = pre[pre[u][i - 1]][i - 1];
		dfn[++cd] = u, st[u] = cd;
		rep(i, 0, sz(g[u])) if(g[u][i] != fa) dfs(g[u][i], u);
		dfn[++cd] = u, ed[u] = cd;
	}
	int lca(int x, int y) {
		if(dep[x] > dep[y]) swap(x, y);
		per(i, 0, M) if(dep[pre[y][i]] >= dep[x]) y = pre[y][i];
		per(i, 0, M) if(pre[x][i] != pre[y][i]) x = pre[x][i], y = pre[y][i];
		if(x == y) return x;
		return pre[x][0];
	}
	void adde(int u, int v, int id) {
		if(st[u] > st[v]) swap(u, v);
		int f = lca(u, v);
		if(f == u) {
			nds.pb(Node(id, st[u], st[v]));
		} else {
			int l = ed[u], r = st[v];
			if(l > r) swap(l, r);
			nds.pb(Node(id, l, r, f));
		}
	}
	ll ans;
	ll res[N][2];
	int inv[(int)1e7 + 7];
	int nfen, tot;
	pair<int, ll> fen[N];
	vector<pii> Q;
#define lb(x) (x & (-x))
	void upd(int p, int a, ll b) {
		p = inv[p];
		for(; p <= nfen; p += lb(p)) fen[p].fi += a, fen[p].se += b;
	}
	void qry(pair<int, ll> &res, int p) {
		p = inv[p];
		int a = 0; ll b = 0;
		for(; p >= 1; p ^= lb(p)) a += fen[p].fi, b += fen[p].se;
		res = mp(a, b);
	}
	void add(int x) {
		++tot;
		pair<int, ll> res;
		qry(res, t[x]);
		ans += res.se + (tot - res.fi) * 1ll * t[x];
		upd(t[x], 1, t[x]);
	}
	void sub(int x) {
		pair<int, ll> res;
		qry(res, t[x]);
		ans -= res.se + (tot - res.fi) * 1ll * t[x];
		upd(t[x], -1, -t[x]);
		--tot;
	}
	void upd(int p, int c) {
		p = dfn[p];
		cnt[p] += c;
		(cnt[p] == 1) ? add(p) : sub(p);
	}
	void solve() {
		rep(i, 0, N << 1) B[i] = i / SZ;
		dfs(rt, cd = 0);
		// adde(u, v)
		int now = 1;
		rep(i, 0, m) {
			string o;
			int x;
			cin >> o >> x;
			Q.pb(mp(o[0] == 'Q', x));
			if(o[0] == 'Q') {
				adde(now, x % n + 1, i);
				adde(now, (x + key) % n + 1, i + m);
			} else {
				now = x;
			}
		}
		sort(all(nds));
		vi v;
		rep(i, 1, n + 1) v.pb(t[i]);
		sort(all(v));
		v.erase(unique(all(v)), v.end());
		nfen = sz(v);
		rep(i, 0, sz(v)) inv[v[i]] = i + 1;
		int l = 1, r = 0;
		rep(i, 0, sz(nds)) {
			Node &nd = nds[i];
			while(r < nd.r) upd(++r, 1);
			while(l > nd.l) upd(--l, 1);
			while(r > nd.r) upd(r--, -1);
			while(l < nd.l) upd(l++, -1);
			if(nd.lca) upd(st[nd.lca], 1);
			// save ans
			res[nd.id % m][nd.id / m] = ans;
			if(nd.lca) upd(st[nd.lca], -1);
		}
		int pr = 0;
		rep(i, 0, m) if(Q[i].fi) {
			ll ans = res[i][pr];
			pr = (ans & 1);
			cout << ans << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> n >> m >> key;
	rep(i, 1, n + 1) cin >> t[i];
	rep(v, 1, n + 1) {
		int u; cin >> u;
		if(u == 0) rt = v;
		else g[u].pb(v);
	}
	MoOnTree::solve();
	return 0;
}
