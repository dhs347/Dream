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
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 505;
ll dis[N], n, m, a[N * 200], b[N * 200], w[N * 200], x;
vector<pii> g[N];
bool ing[N];

// [0,n) init!!
template<class T>
struct Dinic{
    const static int N = 10101 , M = N * 20;
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
            flow += dfs(s, ~0U>>1);
        }
        return flow;
    }
};

Dinic<ll> G;

void spfa(int s) {
	queue<int> q;
	memset(dis, 0x3f, sizeof(dis));
	q.push(s); dis[s] = 0; ing[s] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop(); ing[u] = 0;
		rep(i, 0, sz(g[u])) {
			int v = g[u][i].fi, w = g[u][i].se;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!ing[v]) {
					q.push(v); ing[v] = 1;
				}
			}
		}
	}
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> a[i] >> b[i] >> w[i];
		g[a[i]].pb(mp(b[i], w[i]));
		g[b[i]].pb(mp(a[i], w[i]));
	}
	spfa(1);
	G.ini(n * 2 + 10);
	rep(i, 1, n+1) {
		cin >> x;
		if (i == 1 || i == n) x = pw(60);
		G.link(i, i+n, x);
	}
	rep(i, 1, m+1) {
		if (dis[a[i]] + w[i] == dis[b[i]]) {
			G.link(a[i] + n, b[i], pw(60));
		}
		if (dis[b[i]] + w[i] == dis[a[i]]) {
			G.link(b[i] + n, a[i], pw(60));
		}
	}
	cout << G.run(1, n + n);
	return 0;
}


