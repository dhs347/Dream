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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int cnt[11];
vi g[11];

void solve() {
	int n = 6;
	rep(i, 1, n + 1) cnt[i] = 0, g[i].clear();
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	rep(i, 1, n + 1) ++cnt[sz(g[i])];
	if(cnt[1] == 2) {
		cout << "n-hexane" << endl;
	} else if(cnt[1] == 3) {
		vector<int> vec;
		rep(i, 1, n + 1) if(sz(g[i]) == 3) {
			for(auto j : g[i]) vec.pb(sz(g[j]));
		}
		sort(all(vec));
		if(vec[1] == 2) {
			cout << "3-methylpentane" << endl;
		} else {
			cout << "2-methylpentane" << endl;
		}
	} else {
		if(cnt[2] == 1) {
			cout << "2,2-dimethylbutane" << endl;
		} else {
			cout << "2,3-dimethylbutane" << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
