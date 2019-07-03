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
    const static int N = 200101 , M = N * 10;
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

const int N = 25;
int n, m, s, t, x, y, cnt, dis[N][N], nx, ny, id[N][N];
string ss[N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
vector<pii> V;

int check(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= m || ss[x][y] == 'X') return -1;
	return ss[x][y] == '.';
}

void bfs(int x, int y, int p) {
	queue<pii> q;
	q.push(mp(x, y));
	memset(dis, 0x3f, sizeof(dis)); dis[x][y] = 0;
	while (!q.empty()) {
		int u = q.front().fi, v = q.front().se; q.pop();
		rep(i, 0, 4) {
			nx = u + dx[i];
			ny = v + dy[i];
			if (check(nx, ny) != 1) continue;
			if (dis[nx][ny] > dis[u][v] + 1) {
				dis[nx][ny] = dis[u][v] + 1;
				G.link(id[nx][ny], cnt + p + dis[nx][ny] * sz(V), 1);
				q.push(mp(nx, ny));
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
	rep(i, 0, n) cin >> ss[i];
	rep(i, 0, n) rep(j, 0, m) {
		if (ss[i][j] == '.') id[i][j] = cnt++;
		if (ss[i][j] == 'D') V.pb(mp(i, j));
	}
	G.ini(sz(V) * n * m + 10 + cnt); s = G.n - 4; t = s + 1;
	rep(i, 0, n) rep(j, 0, m) if (ss[i][j] == '.') G.link(s, id[i][j], 1);
	rep(i, 0, sz(V)) bfs(V[i].fi, V[i].se, i);
	int mm = cnt;
	rep(i, 1, n * m + 1) {
		rep(j, 0, sz(V)) {
			G.link(cnt + j + (i - 1) * sz(V), cnt + j + i * sz(V), inf);
			G.link(cnt + j + i * sz(V), t, 1);
		}
		mm -= G.run(s, t);
		if (mm == 0) {
			cout << i << endl;
			return 0;
		}
	}
	cout << "impossible" << endl;
	return 0;
}


