#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 3e5 + 7;
int n, m, a[N], b[N], u, du[N];
vi g[N];
set<pii> M;
set<int> V;
queue<int> q;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> a[i] >> b[i];
		if (M.count(mp(a[i], b[i]))) continue;
		g[a[i]].pb(b[i]);
		g[b[i]].pb(a[i]);
		M.insert(mp(a[i], b[i]));
		M.insert(mp(b[i], a[i]));
		du[a[i]]++;
		du[b[i]]++;
	}
	rep(i, 1, n+1) {
		V.insert(i);
		if (du[i] == 2) q.push(i);
	}
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (du[u] != 2) continue;
		vi t;
	//	de(u);de(du[u]);
		for (auto v : g[u]) {
			if (V.count(v)) t.pb(v);
		}
		V.erase(u);
		if (M.count(mp(t[0], t[1]))) {
			du[t[0]]--;
			if (du[t[0]] == 2) q.push(t[0]);
			du[t[1]]--;
			if (du[t[1]] == 2) q.push(t[1]);
		}else {
			M.insert(mp(t[0], t[1]));
			M.insert(mp(t[1], t[0]));
			g[t[0]].pb(t[1]);
			g[t[1]].pb(t[0]);
		}
	}
	if (sz(V) == 2) {
		cout << "Yes" << endl;
	}else cout << "No" << endl;
	return 0; 
}
