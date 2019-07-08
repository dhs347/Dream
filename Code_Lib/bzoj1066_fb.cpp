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

// [0,n) init!! 
// double need eps  
const int inf = pw(30);
template<class T>
struct Dinic{
    const static int N = 10101 , M = N * 50;
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

Dinic<int> G;

int n, m, d, ans, s, t;
string ss[50];

int id(int i, int j, int k) {
	return i * m + j + k * n * m;
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m >> d; 
	G.ini(n * m * 2 + 10); s = G.n - 5; t = s + 1;
	rep(i, 0, n) cin >> ss[i];
	rep(i, 0, n) rep(j, 0, m) if (ss[i][j] > '0') {
		G.link(id(i, j, 0), id(i, j, 1), ss[i][j] - '0');
		rep(k, 0, n) rep(l, 0, m) if (ss[k][l] > '0' && abs(i - k) + abs(j - l) <= d)
			G.link(id(i, j, 1), id(k, l, 0), inf); 	
		if (i + d >= n || i - d < 0 || j + d >= m || j - d < 0) G.link(id(i, j, 1), t, inf);
	}
	rep(i, 0, n) {
		cin >> ss[i];
		rep(j, 0, m) if (ss[i][j] == 'L') G.link(s, id(i, j, 0), 1), ans++;
	}
	cout << ans - G.run(s, t);
	return 0;
}


