#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e4 + 10;
int n, k, n1, n2, p[N];
string s;
pair<string, int> a[N], b[N];
vi g[N], S[N];

namespace MaxMatch {
	const int N = 10050;
	int link[N], vis[N], use[N], in[N];
	int dfs(int c, vi g[]) {
		for(auto t : g[c]) {
			if(!vis[t] ) {
				vis[t] = 1;
				if(link[t] == -1 || dfs(link[t], g)) {
					return link[t] = c, 1;
				}
			}
		}
		return 0;
	}
	int solve(int n, int m, vi g[]) {
		fill_n(link, m+1, -1);
		int ret = 0;
		rep(i, 1, n+1) {
			memset(vis, 0, (m+1) * sizeof(int));
			ret += dfs(i, g);
		}
		return ret;
	}
	void solve2(int n, vi g[]) {
		queue<int> q;
		memset(vis, 0, sizeof(vis));
		per(i, 1, n+1) if (link[i] != -1) link[link[i]] = i; 
		rep(i, 1, n+1) if (link[i] == -1) use[i] = 1, q.push(i), vis[i] = 1;;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			if (use[u] == 1) {
				for (auto v : g[u]) {
					use[v] = 2;
					if (!vis[v]) {vis[v] = 1;q.push(v);}
				}
			}else {
				int v = link[u];
				use[v] = 1;
				if (!vis[v]) {vis[v] = 1;q.push(v);}
			}
		}
		rep(i, 1, n+1) if (link[i] != -1 && !use[link[i]]) use[i] = 2;
		rep(i, 1, n+1) if (use[i] == 2) {
			vi tmp;
			for (auto v : S[i]) if (!in[v]) {
				in[v] = 1; tmp.pb(v);
			}
			cout << sz(tmp) << " ";
			rep(i, 0, sz(tmp)) cout << tmp[i] << " \n"[i == sz(tmp) - 1];
		}
	}
}

int main() {
	freopen("heavy.in", "r", stdin);
	freopen("heavy.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n+1) {
		cin >> s;
		a[i] = mp(s.substr(0, k), i);
		reverse(all(s));
		b[i] = mp(s.substr(0, k), i);
	}
	sort(a+1, a+n+1);
	sort(b+1, b+n+1);
	rep(i, 1, n+1) {
		if (a[i].fi != a[i-1].fi) n1++;
		S[n1].pb(a[i].se);
		p[a[i].se] = n1;
	}
	rep(i, 1, n+1) {
		if (b[i].fi != b[i-1].fi) n2++;
		S[n2+n1].pb(b[i].se);
		g[p[b[i].se]].pb(n2 + n1);
		g[n2 + n1].pb(p[b[i].se]);
	}
	cout << MaxMatch :: solve(n1, n2+n1, g) << endl;
	MaxMatch :: solve2(n2+n1, g);
	return 0;
}
