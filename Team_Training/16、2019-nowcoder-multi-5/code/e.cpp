#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

char dp[pw(26)];
int msk[26], n, m;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 0, 26) msk[i] |= pw(i);
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		msk[u] |= pw(v);
		msk[v] |= pw(u);
	}
	rep(i, 1, pw(n)) {
		int j = i&(-i);
		j = __builtin_ctz(j);
		dp[i] = dp[i ^ pw(j)];
		int t = i&msk[j];
		dp[i] = max(dp[i], (char)(dp[i ^ t] + 1));
	//	dd(i), de((int)dp[i]);
	}
	int ans = 0;
	rep(i, 0, pw(n)) ans += dp[i];
	cout << ans << endl;
	return 0;
}
