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

const int N = 200;
int n, m, s, t, x, a[N][N], ma, cnt[N], id[N][1000], tid, d, nn;

// [0,n) , init!! , inf modify
template<class U,class V>
struct MCMF{
    static const int N = 6000, M = 201010, inf = 0x3f3f3f3f;
    int h[N], ing[N], pre[N], to[M], ne[M], e, s, t, n;
    U cap[M]; V dis[N], cost[M];
    void ini(int _n = N){ fill(h , h + (n=_n) , -1);e = 0;}
    void liu(int u,int v,U c,V w){ to[e] = v;ne[e] = h[u];cap[e] = c;cost[e] = w;h[u] = e++;}
    void link(int u,int v,U c,V w){ liu(u,v,c,w);liu(v,u,0,-w); }
    bool spfa(){
        queue<int> Q;
        fill(dis, dis+n, inf);
        Q.push(s), ing[s] = 1, dis[s] = 0;
        while(!Q.empty()){
            int c = Q.front(); Q.pop(); ing[c] = 0;
            for(int k = h[c]; ~k; k = ne[k]) if (cap[k] > 0) {
                int v = to[k];
                if(dis[c] + cost[k] < dis[v]){
                    dis[v] = dis[c] + cost[k];
                    pre[v] = k;
                    if(!ing[v]) Q.push(v) , ing[v] = 1;
                }
            }
        }
        return dis[t] != inf;
    }
    U flow; V mincost;
    pair<U, V> run(int _s,int _t){
        s = _s , t = _t;
        flow = mincost = 0;
        while(spfa()){
            U pl = inf; int p, k;
            for(p = t;p != s;p = to[k^1]) pl = min(pl, cap[k = pre[p]]);
            for(p = t;p != s;p = to[k^1]) cap[k = pre[p]] -= pl, cap[k^1] += pl;
            int c = 0; 
			rep(i, 1, m+1) {
				int w = cap[h[id[i][cnt[i]]]];
				if (w == 0) {
					c++;
					cnt[i]++; id[i][cnt[i]] = ++tid;
					rep(j, 1, nn+1) link(j, tid, 1, cnt[i] * a[j][i]);
					link(tid, t, 1, 0);
				}
			}
			assert(c <= 1);
			mincost += pl * dis[t];
            flow += pl;
        }
        return mp(flow, mincost);
    }
};

MCMF<int, int> G;



int main() {
	freopen("a.in","r",stdin);
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	d = 1000;
	cin >> n >> m; s = n + m + d + 1; t = s + 1;
	nn = n;
	G.ini(n + m + d + 10);
	rep(i, 1, n+1) {
		cin >> x;
		G.link(s, i, x, 0);
	}
	rep(i, 1, n+1) rep(j, 1, m+1) cin >> a[i][j], G.link(i, j + n, 1, a[i][j]);
	rep(i, 1, m+1) cnt[i] = 1, G.link(i + n, t, 1, 0), id[i][1] = i + n;
	tid = n + m;
	cout << G.run(s, t).se;
	//rep(i, 1, m+1) de(cnt[i]);
	//de(G.cap[0]);
	return 0;
}


