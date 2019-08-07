#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, h[N];
bool vis[N];

bool check(int x) {
	if(x < 1 || x > n) return 0;
	rep(i, 0, 2) {
		int y = x * 2 + i;
		if(y <= n && !vis[y]) return 0;
	}
	return 1;
}

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> h[i], vis[i] = 0;
	priority_queue<pii> que;
	rep(i, 1, n + 1) if(i * 2 > n) que.push(mp(h[i], i));
	ll ans[2] = {0};
	rep(i, 1, n + 1) {
		auto u = que.top(); que.pop();
		ans[i & 1] += u.fi;
		vis[u.se] = 1;
		if(check(u.se / 2)) que.push(mp(h[u.se / 2], u.se / 2));
	}
	cout << ans[1] << " " << ans[0] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
