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
typedef int db;
typedef vector<int> vi;

const int N = 505;

int a, b, c, n;
db w[N], h[N]; int k[N];
db f[N][N];

vi g[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> a >> b >> c >> n;
	rep(i, 1, n + 1) {
		cin >> w[i] >> h[i] >> k[i];
		rep(j, 1, k[i] + 1) {
			int v; cin >> v;
			g[i].pb(v);
		}
	}
	int fh = h[1];
	f[1][fh] = w[1];
	priority_queue<pair<db, pii> > que;
	que.push(mp(w[1], mp(1, fh)));
	while(!que.empty()) {
		auto u = que.top(); que.pop();
		if(f[u.se.fi][u.se.se] > u.fi) continue;
		for(auto v : g[u.se.fi]) {
			int fhv = min(h[v], u.se.se);
			db t = min(u.fi, w[v]);
			if(f[v][fhv] < t) {
				f[v][fhv] = t;
				que.push(mp(t, mp(v, fhv)));
			}
		}
	}
	if(a < b) swap(a, b);
	if(a < c) swap(a, c);
	db ans = 0;
	db aa, bb;
	rep(i, 1, 300 + 1) {
		db h = min(i, (db)c);
		db w = min(f[n][i], (db)b);
		if(ans < h * w) {
			ans = h * w;
			aa = w;
			bb = h;
		}
		h = min(i, (db)b);
		w = min(f[n][i], (db)c);
		if(ans < h * w) {
			ans = h * w;
			aa = w;
			bb = h;
		}
	}
	cout << a << " " << aa << " " << bb << endl;
	return 0;
}
