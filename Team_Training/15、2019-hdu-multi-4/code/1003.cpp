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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

vi ans[N];

bool cmp(pii a, pii b) {
	return a.fi + a.se > b.fi + b.se;
}

void solve() {
	int n, k; cin >> n >> k;
	if(k == 1) {
		cout << "yes" << endl;
		rep(i, 1, n + 1) cout << i << " \n"[i == n];
		return ;
	}
	if(n * 1ll * (n + 1) / 2 % k || n == k) {
		cout << "no" << endl;
		return ;
	} 
	cout << "yes" << endl;
	int m = n / k; ll M = n * 1ll * (n + 1) / 2 / k;
	int to = (m & 1) ? m - 2 : m, p = 1;
	rep(i, 1, to + 1) {
		if(i & 1) {
			rep(j, 1, k + 1) ans[j].pb(p++);
		} else {
			per(j, 1, k + 1) ans[j].pb(p++);
		}
	}
	if(m & 1) {
		vector<pii> vec;
		int j = n - k;
		rep(i, n - k + 1, n + 1) {
			vec.pb(mp(i, j));
			j -= 2;
			if(j < n - 2 * k + 1) j = n - k - 1;
		}
		sort(all(vec), cmp);
		rep(i, 0, k) ans[i + 1].pb(vec[i].fi), ans[i + 1].pb(vec[i].se);
	}
	rep(i, 1, k + 1) {
		ll S = 0;
		rep(j, 0, m) cout << ans[i][j] << " \n"[j == m - 1], S += ans[i][j];
		assert(S == M);
	}
	rep(i, 1, k + 1) ans[i].clear();
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

