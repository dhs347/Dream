#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 5e5 + 5;

int n, q, pre[N], now[N];
bool Q[N];
vi g[N];
vector<pii> dur[N];

// N is 2 size of tree , id of nodes start from 1
struct LCARMQ{
	static const int N = 101010 << 1;
	int a[20][N] , lft[N] , dep[N] , lg[N] , L;
	int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
	void add(int x){ a[0][L++] = x;}
	void dfs(int c,int fa,const vi g[]){
		lft[c]=L;add(c);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
		}
	}
	void Build(const vi g[]){
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
	int dis(int x, int y) {
		return dep[x] + dep[y] - 2 * dep[lca(x, y)];
	}
}R;

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	vi nd[N];
	int st, ed, now;
	void upd(int L, int R, int u, int l, int r, int rt) {
		if(L <= l && r <= R) {
			nd[rt].pb(u);
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, u, l, mid, ls);
		if(R > mid) upd(L, R, u, mid + 1, r, rs);
	}
	void dfs(int l, int r, int rt) {
		int ps = st, pe = ed, pn = now;
		rep(i, 0, sz(nd[rt])) {
			int u = nd[rt][i];
			if(now == -1) {
				st = ed = u; now = 0;
				continue;
			}
			int ds = R.dis(u, st);
			int de = R.dis(u, ed);
			if(ds >= de && ds > now) ed = u, now = ds;
			else if(de >= ds && de > now) st = u, now = de;
		}
		if(l < r) {
			int mid = l + r >> 1;
			dfs(l, mid, ls);
			dfs(mid + 1, r, rs);
		} else {
			if(Q[l]) cout << now << endl;
		}
		st = ps, ed = pe, now = pn;
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v; cin >> u >> v; 
		g[u].pb(v), g[v].pb(u);
	}
	R.Build(g);
	cin >> q;
	rep(i, 1, q + 1) {
		string s; int x;
		cin >> s;
		if(s[0] == 'G') {
			Q[i] = 1;
		} else {
			cin >> x;
			if(!now[x]) dur[x].pb(mp(pre[x], i));
			else pre[x] = i;
			now[x] ^= 1;
		}
	}
	seg.now = -1;
	rep(i, 1, n + 1) if(!now[i]) dur[i].pb(mp(pre[i], q));
	rep(i, 1, n + 1) {
		rep(j, 0, sz(dur[i])) {
			pii e = dur[i][j];
			seg.upd(e.fi, e.se, i, 0, q, 1);
		}
	}
	seg.dfs(0, q, 1);
	return 0;
}
