int n, a[N]; vi g[N];
namespace DP {
	int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N], leaf[N];
	ll f[N][2], F[N][2];
	struct Mat {
		ll a[3][3];
		inline Mat operator * (const Mat &c) const {
			Mat r; rep(i, 0, 3) rep(j, 0, 3) {
				r.a[i][j] = a[i][0] + c.a[0][j];
				rep(k, 1, 3) r.a[i][j] = max(r.a[i][j], a[i][k] + c.a[k][j]);
			} return r;
		}
		inline void e() { rep(i, 0, 3) rep(j, 0, 3) a[i][j] = (i != j) * (-inf); }
	};
	struct Seg {
		Mat m[N << 2];
		inline void build(int l, int r, int rt) {
			if(l == r) {
				int u = who[l];
				// calc F, f
				// set m[rt]
				return ;
			}
			int mid = l + r >> 1; build(mid + 1, r, rs); build(l, mid, ls);
			m[rt] = m[ls] * m[rs];
		}
		inline void upd(int u, int l, int r, int rt) {
			if(l == r) {
				// set m[rt]
				return ;
			}
			int mid = l + r >> 1;
			(id[u] <= mid) ? upd(u, l, mid, ls) : upd(u, mid + 1, r, rs);
			m[rt] = m[ls] * m[rs];
		}
		inline void qry(int L, int R, int l, int r, int rt, Mat &ans) {
			if(rt == 1) ans.e();
			if(L <= l && r <= R) return ans = ans * m[rt], void();
			int mid = l + r >> 1;
			if(L <= mid) qry(L, R, l, mid, ls, ans);
			if(R > mid) qry(L, R, mid + 1, r, rs, ans);
		}
	}seg;
	struct HeavyChain{
		// if(s) top[s] = top[c], dfs2(s, c, g), leaf[c] = leaf[s];
		// else leaf[c] = c;
	}hc;
	inline pair<ll, ll> qry(int x) {
		Mat tmp; seg.qry(id[x], id[leaf[x]], 1, n, 1, tmp);
		ll f0 = max(tmp.a[0][0], tmp.a[0][1], tmp.a[0][2]);
		ll f1 = max(tmp.a[1][0], tmp.a[1][1], tmp.a[1][2]);
		return mp(f0, f1);
	}
	void upd(int p, int c) {
		F[p][1] += c - a[p], a[p] = c;
		int v = p;
		while(v) {
			int u = top[v], fa = par[u];
			seg.upd(v, 1, n, 1);
			pair<ll, ll> _f = qry(u);
			if(fa) {
				// upd F[fa]
			}
			f[u][0] = _f.fi, f[u][1] = _f.se, v = fa;
		}
	}
	void work() {
		hc.Build(g);
		seg.build(1, n, 1);
	}
}
