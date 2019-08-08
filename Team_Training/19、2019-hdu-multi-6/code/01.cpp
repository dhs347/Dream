#pragma comment(linker, "/STACK:102400000,102400000") 
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
//typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 3e5 + 7; 
int x, k, w, a[N], n, m, T, u, len[N];
ll cost[N], ans;
vi g[N];
vector<pii> gg[N];
struct LongChain{
	static const int N = ::N;
	map<int, ll> v[N];
	int wson[N] , top[N] , dep[N] , lg[N], st[N];
	int jump[N][20] , id[N] , who[N] , rwho[N] , _;
	void dfs(int c,int fa,vi g[]){
		dep[c]=1;int &s=wson[c]=top[c]=0;
		jump[c][0]=fa;rep(i,1,20) jump[c][i]=jump[jump[c][i-1]][i-1];
		for(auto t:g[c]) if(t!=fa)
			dfs(t,c,g),dep[c]=max(dep[t]+1,dep[c]),(dep[t]>=dep[s])&&(s=t);
	}
	void dfs2(int c,int fa,int rc,vi g[]){
		if(!top[c]) top[c]=c,rc=c;
		who[id[c]=++_]=c;rwho[_]=rc;
		int s=wson[c];
		if(s) top[s]=top[c],dfs2(s,c,jump[rc][0],g);
		for(auto t:g[c]) if(t!=fa&&t!=s) dfs2(t,c,t,g);
	}
	void Build(vi g[]){
		dfs(1,0,g);_=0;dfs2(1,0,1,g);
		rep(i,2,N) lg[i]=lg[i>>1]+1;
	}
	void solve(int c, int fa, vi g[]) {
		v[c].clear();
		for(auto t : g[c]) if(t != fa) solve(t, c, g);
		if(wson[c]) {
			// upd c by wson[c], O(1) or O(log(n))
			st[c] = st[wson[c]] - 1;
			v[c].swap(v[wson[c]]);
			//v[c] = v[wson[c]];
			v[c][st[c]] = a[c];
		} else {
			// c is leaf
			st[c] = 0;
			v[c][0] = a[c];
		}
		for(auto t : g[c]) if(t != fa && t != wson[c]) {
			// brute force upd c by t
			for (auto u : v[t]) {
				v[c][st[c] + u.fi - st[t] + 1] += u.se;
			}
		}
		for (auto cam : gg[c]) {
			auto u = v[c].upper_bound(st[c] + cam.fi);
			if (u == v[c].begin()) continue;
			u--; ll cost = cam.se;
			while (1) {
				ll tmp = min((*u).se, cost);
				ans -= tmp;
				cost -= tmp;
				(*u).se -= tmp;
				if ((*u).se == 0) {
					if (u == v[c].begin()) {
						v[c].erase(u);
						break;
					}
					v[c].erase(u--);		
				}else break;
			}
		}
		// 注意统计以 c 为起点的链的答案，注意深度的限制（两棵子树都要注意） 
	}
}hc;


int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) g[i].clear(), gg[i].clear();
		rep(i, 2, n+1) {
			cin >> u;
			g[u].pb(i);
		}
		ans = 0;
		rep(i, 1, n+1) cin >> a[i], ans += a[i];
		rep(i, 1, m+1) {
			cin >> x >> k >> w;
			gg[x].pb(mp(k, w));
		}
		hc.Build(g);
		hc.solve(1, 0, g);
		cout << ans << endl;
	}	
	return 0;
}


