#include <bits/stdc++.h>
#include <map> 
#include <cstring>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define de(x) cout<<#x<<" = "<<x<<"\n"
#define dd(x) cout<<#x<<" = "<<x<<" "
#define mes(p) memset(p,0,sizeof(p))
#define all(x) x.begin(),x.end()
#define rson mid+1,r,rt<<1|1
#define sz(x) (int)x.size()
#define lson l,mid,rt<<1
#define pb push_back
#define mp make_pair
#define ls (rt<<1)
#define se second
#define rs (ls|1)
#define fi first
typedef pair <int ,int > pii;
typedef vector <int > vi;
typedef long long ll;
const int maxn=3000005;
const ll mod = 1e9+ 7;

const int N = 101010;

int n, q, pre[N], rk[N], dfn[N], id[N], dep[N], st[N], ed[N];
pii dia[N];
pair<pii, int> e[N];
ll ans[N];
vi g[N];

struct LCARMQ{
	static const int N = 101010 << 1;
	int a[20][N] , lft[N], lg[N] , L, cntd;
	int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
	void add(int x){ a[0][L++] = x;}
	void dfs(int c,int fa,const vi g[]){
		dfn[++cntd] = c;
		id[c] = st[c] = cntd;
		lft[c]=L;add(c);
		for(auto t : g[c]) if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
		ed[c] = cntd;
	}
	void build(const vi g[]){
		L = 0;dfs(1,0,g);dep[0] = -1;
		rep(i,2,L) lg[i]=lg[i>>1]+1;
		rep(i,1,20){
			int lim = L+1-(1<<i);
			rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
		}
	}
	int lca(int x,int y){
		x = lft[x] , y = lft[y];
		if(x > y) swap(x , y);
		int i = lg[y-x+1];
		return rmin(a[i][x] , a[i][y+1-(1<<i)]);
	}
}R;

struct Node {
	string o; int x, y;
	Node() {}
	Node(string o, int x, int y) : o(o), x(x), y(y) {}
}nd[N];

struct Seg2 {
	static const int N = ::N << 2;
	ll a[N];
	void upd(int L, int R, ll c, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) {
			a[rt] += c;
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
	}
	ll qry(int p, int l = 1, int r = n, int rt = 1) {
		if(rt == 1) p = id[p];
		if(l == r) return a[rt];
		int mid = l + r >> 1; 
		if(p <= mid) return a[rt] + qry(p, l, mid, ls);
		else return a[rt] + qry(p, mid + 1, r, rs);
	}
}seg2;

int find(int x) {
	return x == pre[x] ? x : find(pre[x]);
}
ll dis(int x, int y) {
	return seg2.qry(x) + seg2.qry(y) - 2 * seg2.qry(R.lca(x, y));
}
pii gao(pii a, pii b) {
	int arr[] = {a.fi, a.se, b.fi, b.se};
	int x, y; ll d = -1;
	rep(i, 0, 4) rep(j, i + 1, 4) {
		auto t = dis(arr[i], arr[j]);
		if(t > d) {
			d = t, x = arr[i], y = arr[j];
		}
	}
	return mp(x, y);
}
void join(int x, int y, vector<pii> &v3, vi &v4, vector<pair<int, pii> > &v5) {
	x = find(x), y = find(y);
	if(rk[x] > rk[y]) swap(x, y);
	v3.pb(mp(x, pre[x]));
	pre[x] = y; 
	if(rk[x] == rk[y]) ++rk[y];
	v4.pb(y);
	v5.pb(mp(y, dia[y]));
	dia[y] = gao(dia[x], dia[y]);
}

struct Seg {
	static const int N = ::N << 2;
	vector<pii> vec[N];
	void upd(int L, int R, pii c, int l = 1, int r = q, int rt = 1) {
		if(L <= l && r <= R) return vec[rt].pb(c), void();
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
	}
	void dfs(int l = 1, int r = q, int rt = 1) {
		vector<pair<pii, int> > v1; 
		vector<pii> v2, v3;
		vi v4;
		vector<pair<int, pii> > v5;
		for(auto u : vec[rt]) {
			int v = e[u.fi].fi.se;
			seg2.upd(st[v], ed[v], u.se - e[u.fi].se);
			v1.pb(mp(mp(st[v], ed[v]), e[u.fi].se - u.se));
			v2.pb(mp(u.fi, e[u.fi].se));
			e[u.fi].se = u.se;
			join(e[u.fi].fi.fi, v, v3, v4, v5);
		}
		if(l == r) {
			if(nd[l].o[0] == 'Q') {
				int t = find(1);
				ans[l] = max(dis(nd[l].x, dia[t].fi), dis(nd[l].x, dia[t].se));
			}
		} else {
			int mid = l + r >> 1;
			dfs(l, mid, ls);
			dfs(mid + 1, r, rs);
		}
		for(auto u : v1) seg2.upd(u.fi.fi, u.fi.se, u.se);
		reverse(all(v2));
		for(auto u : v2) e[u.fi].se = u.se;
		reverse(all(v3));
		for(auto u : v3) pre[u.fi] = u.se;
		for(auto u : v4) --rk[u];
		reverse(all(v5));
		for(auto u : v5) dia[u.fi] = u.se;
	}
}seg;

void adde(int L, int R, int x, int y) {
	if(L > R) return ;
	seg.upd(L, R, mp(x, y));
}
void read(int tim) {
	string o; int x, y;
	cin >> o >> x;
	if(o[0] == 'C') {
		cin >> y;
		adde(pre[x], tim - 1, x, e[x].se);
		e[x].se = y; pre[x] = tim;
	}
	nd[tim] = Node(o, x, y);
}

int main(){	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		cin >> e[i].fi.fi >> e[i].fi.se >> e[i].se;
		int u = e[i].fi.fi, v = e[i].fi.se;
		g[u].pb(v); g[v].pb(u);
	}
	R.build(g);
	rep(i, 1, n) {
		int &u = e[i].fi.fi, &v = e[i].fi.se;
		if(dep[u] > dep[v]) swap(u, v);
	}
	cin >> q;
	rep(i, 1, n) pre[i] = 1;
	rep(i, 1, q + 1) read(i);
	rep(i, 1, n) adde(pre[i], q, i, e[i].se);

	memset(ans, -1, sizeof(ans));
	rep(i, 1, n + 1) pre[i] = i, dia[i] = mp(i, i), rk[i] = 0;
	rep(i, 1, n) e[i].se = 0;
	seg.dfs();
	rep(i, 1, q + 1) if(~ans[i]) cout << ans[i] << endl;
	return 0;
}
