#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> a[i] >> b[i];
		V[0].pb(a[i]);
		V[1].pb(b[i]);
	}
	cin >> m;
	rep(i, 0, 2) {
		sort(all(V[i]));
		V[i].erase(unique(all(V[i])). V[i].end());
	}
	rep(i, 0, sz(V[0])) lr[p] = pw(30);
	rep(i, 0, sz(V[1])) lc[p] = pw(30);
	rep(i, 1, m+1) {
		cin >> s >> p >> k;
		if (s[0] == "R") {
			p = lower_bound(all(V[0]), p) - V[0].begin();
			lr[p] = min(lr[p], k);
		}else {
			p = lower_bound(all(V[1]), p) - V[1].begin();
			lc[p] = min(lc[p], k);
		}
	}
	return 0;
}
