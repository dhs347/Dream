#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

template<class T> 
struct Dinic {
	const static int N = 20101, M = N * 10;
	int s, t, n, h[N], cur[N], level[N], q[N], e, ne[M], to[M];
	T cap[M], flow;
	void liu(int u, int v, T w) {
		to[e] = v, ne[e] = h[u], cap[e] = w; h[u] = e++;
	}
	void link(int u, int v, T w) {
		liu(u, v, w);
		liu(v, u, 0);
	}
	void init(int _n = N) {
		fill(h, h + (n = _n), -1); e = 0;
	}
	bool bfs() {
		int L = 0, R = 0;
		fill(level, level + n, -1);
		level[q[R++] = s] = 0;
		while(L < R && level[t] == -1) {
			int c = q[L++];
			for(int k = h[c]; ~k; k = ne[k]) {
				if(cap[k] > 0 && level[to[k]] == -1) {
					level[q[R++] = to[k]] = level[c] + 1;
				}
			}
		}
		return ~level[t];
	}
	T dfs(int c, T mx) {
		if(c == t) return mx;
		T ret = 0;
		for(int &k = cur[c]; ~k; k = ne[k]) {
			if(level[to[k]] == level[c] + 1 && cap[k] > 0) {
				T flow = dfs(to[k], min(mx, cap[k]));
				ret += flow; cap[k] -= flow, cap[k ^ 1] += flow; mx -= flow;
				if(!mx) return ret;
			}
		}
		level[c] = -1;
		return ret;
	}
	T run(int _s, int _t) {
		s = _s, t = _t;
		flow = 0;
		while(bfs()) {
			copy(h, h + n, cur);
			flow += dfs(s, ~0U >> 1);
		}
		return flow;
	}
};


Dinic<int> G;

const int N = 105;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int an[] = {'v', '^', '>', '<'};
int ans, cnt[N], n, m, s, t, p[N], x, y, nx, ny, o, op[N];
string ss[N];


int id(int x, int y) {
	return x * m + y;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	G.init(n * m + 100);s = G.n - 5; t = s + 1;
	rep(i, 0, 26) p[i] = G.n - 50 + i; 
	rep(i, 0, n) cin >> ss[i];
	
	rep(i, 0, n) {
		rep(j, 0, m) {	
			if (ss[i][j] == '*') ans++;
			else if (ss[i][j] != '.') cnt[ss[i][j] - 'A']++;
			o = (i + j) & 1;
			if (o) {
				if (ss[i][j] == '*') G.link(s, id(i, j), 1);
				else if (ss[i][j] != '.') op[ss[i][j] - 'A'] = o, G.link(p[ss[i][j] - 'A'], id(i, j), 1);
			}
			else {
				if (ss[i][j] == '*') G.link(id(i, j), t, 1);
				else if (ss[i][j] != '.') op[ss[i][j] - 'A'] = o, G.link(id(i, j), p[ss[i][j] - 'A'], 1);
			}
			if (o) {
				rep(k, 0, 4) {
					nx = i + dx[k], ny = j + dy[k];
					if (nx >= 0 && nx < n && ny < m && ny >= 0 && ss[nx][ny] != '.') G.link(id(i, j), id(nx, ny), 1); 
				}
			}
		}	
	}

	rep(i, 0, 26) if (op[i]) G.link(s, p[i], 1);else G.link(p[i], t, 1);

	rep(i, 0, 26) ans += cnt[i] > 0;
	if (ans == G.run(s, t) * 2) {
		for (int i = 0; i < G.e; i += 2) {
			int u = G.to[i ^ 1], v = G.to[i];
			if (u <= n * m && v <= n * m && u != s && v != t && G.cap[i] == 0) {
				int x = u / m, y = u % m, nx = v / m, ny = v % m;
				rep(k, 0, 4) {
					if (x + dx[k] == nx && y + dy[k] == ny) {
						ss[x][y] = an[k];
						ss[nx][ny] = an[k ^ 1];
					}
				}
			} 
		}
		rep(i, 0, n) rep(j, 0, m) if (ss[i][j] >= 'A' && ss[i][j] <= 'Z') ss[i][j] = '@';
		cout << "Yes" << endl;
		rep(i, 0, n) cout << ss[i] << endl;
	}else {
		cout << "No" << endl;
	}
	return 0;
}
