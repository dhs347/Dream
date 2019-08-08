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
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int T, A, B, C, c[50], a[50], b[50];
ll dp[50][2][2][2][2];

void work(int *a, int b) {
	int len = 0;
	rep(i, 0, 32) a[i] = 0;
	while (b) a[len++] = b % 2, b >>= 1;
}

ll dfs(int pos, int o1, int o2, int lim1, int lim2) {
	if (pos < 0) return 1;
	ll &t = dp[pos][o1][o2][lim1][lim2];
	if (t != -1) return t;
	int up1 = o1 == 1 ? a[pos] : 1;
	int up2 = o2 == 1 ? b[pos] : 1;
	ll res = 0;
	rep(i, 0, up1 + 1)
		rep(j, 0, up2 + 1) {
			int t1 = i & j;
			int t2 = i ^ j;
			if (lim1 && t1 > c[pos]) continue;
			if (lim2 && t2 < c[pos]) continue;
			res = res + dfs(pos-1, o1 && (i == up1), o2 && (j == up2), lim1 && (t1 == c[pos]), lim2 && (t2 == c[pos]));
		}
	return t = res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> A >> B >> C;
		work(a, A);
		work(b, B);
		work(c, C);
		memset(dp, -1, sizeof(dp));
		ll ans = dfs(31, 1, 1, 1, 1);
		ans -= max(0, B - C + 1);
		ans -= max(0, A - C + 1);
		cout << 1ll * A * B - ans << endl;
	}
	return 0;
}
