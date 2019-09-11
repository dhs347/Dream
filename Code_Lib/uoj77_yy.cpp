#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 5050;
const int inf=1e9;

int n, rt[N];
vi V;

int F(int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

struct Node {
	int a, b, w, l, r, p;
	void read(int i) {
		cin >> a >> b >> w >> l >> r >> p;
		V.pb(a);
	}
}nd[N];

template<class T>
struct Dinic{
	const static int N = 201010 , M = N * 10;
	int s , t , n , h[N] , cur[N] , lv[N] , q[N] , e , ne[M] , to[M];
	T cap[M] , flow;
	void liu(int u,int v,T w){ to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
	void link(int u,int v,T w){ liu(u , v , w);liu(v , u , 0);}
	void ini(int _n = N) { fill(h , h + (n=_n) , -1);e = 0;}
	bool bfs(){
		int L = 0 , R = 0;
		fill(lv , lv + n , -1);
		lv[q[R++] = s] = 0;
		while(L < R && !~lv[t]){
			int c = q[L++];
			for(int k = h[c]; ~k ; k = ne[k])
				if(cap[k] > 0 && !~lv[to[k]]) 
					lv[q[R++] = to[k]] = lv[c] + 1;
		}
		return ~lv[t];
	}
	T dfs(int c,T mx){
		if(c == t) return mx;
		T ret = 0;
		for(int &k = cur[c]; ~k; k = ne[k]){
			if(lv[to[k]] == lv[c] + 1 && cap[k] > 0){
				T flow = dfs(to[k] , min(mx , cap[k]));
				ret += flow;cap[k] -= flow , cap[k^1] += flow;mx -= flow;
				if(!mx) return ret;
			}
		}
		lv[c] = -1;
		return ret;
	}
	T run(int _s,int _t){
		s = _s , t = _t;
		flow = 0;
		while(bfs()){
			copy(h , h + n , cur);
			flow += dfs(s, ~0LU>>1);
		}
		return flow;
	}
};

Dinic<ll> G;
vector<pair<pii, ll> > vec;

struct Seg {
	static const int N = ::N * 14;
	int ls[N], rs[N], cntn;
	int upd(int p, int pre, int &now, int fa = 0, int l = 1, int r = n) {
		now = ++cntn;
		//if(fa) vec.pb(mp(pii(fa + n + 1, now + n + 1), ~0LU >> 1));
		ls[now] = ls[pre];
		rs[now] = rs[pre];
		if(l == r) {
		    if (now && pre) vec.pb(mp(pii(now + n + 1, pre + n + 1), ~0LU >> 1));
		    return cntn;
        }
		int mid = l + r >> 1;
		if(p <= mid) return upd(p, ls[pre], ls[now], now, l, mid);
		else return upd(p, rs[pre], rs[now], now, mid + 1, r);
	}
	void qry(int u, int rt, int L, int R, int l = 1, int r = n) {
		if(L > R || !rt) return ;
		if(L <= l && r <= R) return vec.pb(mp(pii(u, rt + n + 1), ~0LU >> 1)), void();
		int mid = l + r >> 1;
		if(L <= mid) qry(u, ls[rt], L, R, l, mid);
		if(R > mid) qry(u, rs[rt], L, R, mid + 1, r);
	}
}seg;


void file_put() {
    freopen("filename.in", "r", stdin);
    //freopen("filename.out", "w", stdout);
}

int main() {
    file_put(); 
     
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n; rep(i, 1, n + 1) nd[i].read(i);
	sort(all(V)); V.erase(unique(all(V)), V.end());
	int S = 0, T = 1;
	rep(i, 1, n + 1) {
		int p = F(nd[i].a);
		int u = seg.upd(p, rt[i - 1], rt[i]) + n + 1;
		vec.pb(mp(pii(S, u), nd[i].b));
		vec.pb(mp(pii(u, T), nd[i].w));
		vec.pb(mp(pii(u, i + 1), nd[i].p));
		seg.qry(i + 1, rt[i - 1], F(nd[i].l), upper_bound(all(V), nd[i].r) - V.begin());
	}
	G.ini(2 + n + seg.cntn + 10);
	rep(i, 1, seg.cntn+1) {
	    if (seg.ls[i]) G.link(i + n + 1, seg.ls[i] + n + 1, ~0LU >> 1);
	    if (seg.rs[i]) G.link(i + n + 1, seg.rs[i] + n + 1, ~0LU >> 1);
    }
	for(auto u : vec) G.link(u.fi.fi, u.fi.se, u.se);
	ll ans = 0;
	rep(i, 1, n + 1) ans += nd[i].w + nd[i].b;
	cout << ans - G.run(S, T) << endl;


//    int S=0,T=2*n+1;
//    G.ini(2*n+2);
//    rep(i,1,n+1) G.link(S,2*i-1,nd[i].b),G.link(2*i-1,T,nd[i].w),G.link(2*i-1,2*i,nd[i].p);
//    rep(i,1,n+1) rep(j,1,i) if (nd[i].l<=nd[j].a && nd[j].a<=nd[i].r) G.link(2*i,2*j-1,inf);
//    ll ans = 0;
//	rep(i, 1, n + 1) ans += nd[i].w + nd[i].b;
//    cout<<ans-G.run(S,T)<<endl;
	
	return 0;
}

