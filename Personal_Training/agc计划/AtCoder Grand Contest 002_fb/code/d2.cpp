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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 2e5 + 7;
int fa[N], siz[N], ans[N], n, m, u, v, Q, x, y, z;

struct node{
	int id, x, y, z;
} q[N], tl[N], tr[N];

int cnt = 0;

int get(int x, vector<pair<int, pii> > &g) {
	if (x == fa[x]) return x;
	int t = get(fa[x], g);
	g.pb(mp(x, mp(fa[x], siz[x])));
	fa[x] = t;
	return t;
}

void merge(int u, int v, vector<pair<int, pii> > &g) {
	u = get(u, g);
	v = get(v, g);
	if (u != v) {
		g.pb(mp(u, mp(u, siz[u])));
		g.pb(mp(v, mp(v, siz[v])));
		fa[u] = v;
		siz[v] += siz[u];
	}
}

int qry(int u, int v, vector<pair<int, pii> > &g) {
	u = get(u, g);
	v = get(v, g);
	if (u == v) return siz[u];
	else return siz[u] + siz[v];
}

void solve(int ql, int qr, int l, int r) {
	if (ql > qr) return;
	if (l == r) {
		rep(i, ql, qr+1) if (q[i].id) ans[q[i].id] = l;
		return;
	}
	int mid = l + r >> 1, cl = 0, cr = 0;
	vector<pair<int, pii> > rev;
	rep(i, ql, qr+1) {
		if (!q[i].id) {
			if (q[i].z > mid) tr[cr++] = q[i];
			else {
				tl[cl++] = q[i];
				merge(q[i].x, q[i].y, rev);
			} 
		}else {
			int t = qry(q[i].x, q[i].y, rev);
			if (t >= q[i].z) tl[cl++] = q[i];
			else tr[cr++] = q[i];
		}
	}
	rep(i, ql, ql + cl) q[i] = tl[i - ql];
	rep(i, ql + cl, qr+1) q[i] = tr[i - ql - cl];
	solve(ql + cl, qr, mid+1, r);
	per(i, 0, sz(rev)) {
		auto u = rev[i];
		fa[u.fi] = u.se.fi;
		siz[u.fi] = u.se.se;
	}
	//de(cnt);
	solve(ql, ql + cl - 1, 1, mid);
}

int main() {
	//FI(a);
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) fa[i] = i, siz[i] = 1;
	rep(i, 1, m+1) {
		cin >> u >> v;
//		u = rnd(1, n);
//		v = rnd(1, n);
		q[i] = {0, u, v, i};
	}
	cin >> Q;
	rep(i, 1, Q+1) {
		cin >> x >> y >> z;
//		x = rnd(1, n);
//		y = rnd(1, n);
//		z = rnd(1, n);
		q[i + m] = {i, x, y, z};
	}
	solve(1, m + Q, 1, m);
	rep(i, 1, Q+1) cout << ans[i] << endl;
	//de(cnt);
	return 0;
}


