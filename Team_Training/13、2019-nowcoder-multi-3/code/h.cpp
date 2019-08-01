#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int inf = 999000000;

void solve() {
	vector<pii> vec;
	int n; cin >> n;
	rep(i, 1, n + 1) {
		int x, y; cin >> x >> y;
		vec.pb(mp(x, y));
	}
	sort(all(vec));
	int m = n / 2 - 1;
	int x = vec[m].fi, y = vec[m].se;
	cout << x - 1 << " " << y + inf + 1 << " " << x + 1 << " " << y - inf << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
