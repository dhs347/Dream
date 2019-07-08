#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class U,class V>
struct MCMF{
    static const int N = 2005 , M = 101010, inf = pw(30);
    int h[N] , ing[N] , pre[N] , to[M] , ne[M] , e , s , t , n;
    U cap[M];V dis[N] , cost[M];
    void ini(int _n = N){ fill(h , h + (n=_n) , -1);e = 0;}
    void liu(int u,int v,U c,V w){ to[e] = v;ne[e] = h[u];cap[e] = c;cost[e] = w;h[u] = e++;}
    void link(int u,int v,U c,V w){ liu(u,v,c,w);liu(v,u,0,-w); }
    bool spfa(){
        queue<int> Q;
        fill(dis,dis+n, inf);
        ing[s] = true , dis[s] = 0;
        Q.push(s);
        while(!Q.empty()){
            int c = Q.front();Q.pop();ing[c] = false;
            for(int k=h[c];~k;k=ne[k]){
                int v = to[k];
                if(cap[k] <= 0) continue;
                if(dis[c] + cost[k] < dis[v]){
                    dis[v] = dis[c] + cost[k];
                    pre[v] = k;
                    if(!ing[v]) Q.push(v) , ing[v] = true;
                }
            }
        }
        return dis[t] <= 0;
    }
    U flow;V mincost;
    pair<U,V> run(int _s,int _t){
        s = _s , t = _t;
        flow = mincost = 0;
        while(spfa()){
            U pl = inf;int p , k;
            for(p=t;p!=s;p=to[k^1]) pl = min(pl , cap[k=pre[p]]);
            for(p=t;p!=s;p=to[k^1]){
                k = pre[p];
                cap[k] -= pl;
                cap[k^1] += pl;
            }
            mincost += pl * dis[t];
            flow += pl;
        }
        return make_pair(flow , mincost);
    }
};

MCMF<int, int> G;
const int N = 1005;
int n, a[N], b[N], m, p, k, lc[N], lr[N], s, t, u, v;
vi V[2];
int main() {
	freopen("a.in", "r", stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n; 
	rep(i, 1, n+1) {
		cin >> a[i] >> b[i];
		V[0].pb(a[i]);
		V[1].pb(b[i]);
	}
	cin >> m;
	rep(i, 0, 2) {
		sort(all(V[i]));
		V[i].erase(unique(all(V[i])), V[i].end());
	}
	rep(i, 0, sz(V[0])) lr[i] = pw(30);
	rep(i, 0, sz(V[1])) lc[i] = pw(30);
	rep(i, 1, m+1) {
		string s;
		cin >> s >> p >> k;
		if (s[0] == 'R') {
			p = lower_bound(all(V[0]), p) - V[0].begin();
			lr[p] = min(lr[p], k);
		}else {
			p = lower_bound(all(V[1]), p) - V[1].begin();
			lc[p] = min(lc[p], k);
		}
	}
	rep(i, 1, sz(V[0])) lr[i] = min(lr[i], lr[i - 1]);
	rep(i, 1, sz(V[1])) lc[i] = min(lc[i], lc[i - 1]);
	s = sz(V[0]) + sz(V[1]) + 1; t = s + 1;
	G.ini(s + 10);
	G.link(s, 0, lr[0], 0);
	rep(i, 1, sz(V[0])) G.link(i - 1, i, lr[i], 0);
	rep(i, 1, n+1) {
		u = lower_bound(all(V[0]), a[i]) - V[0].begin();
		v = lower_bound(all(V[1]), b[i]) - V[1].begin();
		G.link(u, v + sz(V[0]), 1, -i);
	}
	per(i, 1, sz(V[1])) G.link(i + sz(V[0]), i + sz(V[0]) - 1, lc[i], 0);
	G.link(sz(V[0]), t, lc[0], 0);
	cout << -G.run(s, t).se << endl;
	return 0;
}
