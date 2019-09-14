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


const int N = 1e5 + 6;
int T, n, m, k, u[N * 2], v[N * 2], x, y, cnt[N], du[N], r, ok[N], fa[N];
vi g[N];
db ans, sum;

int get(int x) {
	if (x == fa[x] ) return x;
	return fa[x] = get(fa[x]);
}

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> k;
		rep(i, 1, n+1) fa[i] = i, ok[i] = 0, cnt[i] = 0, g[i].clear(), du[i] = 0;
		rep(i, 1, m+1) {
			cin >> u[i] >> v[i];
		}
		rep(i, 1, k+1) {
			cin >> x;
			ok[x] = 1;
		}
		rep(i, 1, m+1) {
			x = u[i]; y = v[i];
			x = get(x); y = get(y);
			if (!ok[x] && !ok[y] && x != y) fa[x] = y;
		}
		rep(i, 1, n+1) if (!ok[i]) cnt[get(i)]++;
		rep(i, 1, m+1) {
			x = u[i]; y = v[i];
			x = get(x); y = get(y);
			du[x]++; du[y]++;
			g[x].pb(y);
			g[y].pb(x);
		}
		r = get(1);
		ans = cnt[r];
		for (auto t : g[r]) if (ok[t]) {
			sum = cnt[r];
			for (auto v : g[t]) if (v != r) { sum += 1.0 / du[t] * cnt[get(v)];}
			ans = max(ans, sum);
		}
		printf("%.10f\n", ans);
	}
	return 0;
}
