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

map<ll, int> tr;
vector<pii> ans;

int solve(ll n) {
	if(n == 1) {
		if(!tr.count(1)) {
			tr[1] = sz(ans);
			ans.pb(mp(-1, -1));
			return sz(ans) - 1;
		}
		return tr[1];
	}
	if(tr.count(n)) return tr[n];
	int ls = solve(n - n / 2), rs = solve(n / 2);
	tr[n] = sz(ans);
	ans.pb(mp(ls, rs));
	return sz(ans) - 1;
}

void solve() {
	ll n; cin >> n;
	tr.clear();
	ans.clear();
	int res = solve(n);
	cout << sz(ans) << endl;
	for(auto u : ans) cout << u.fi << " " << u.se << endl;
	cout << res << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T; 
	while(T--) {
		solve();
	}
	return 0;
}
