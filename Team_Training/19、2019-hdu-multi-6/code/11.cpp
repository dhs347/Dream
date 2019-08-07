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
typedef unsigned long long ull;
typedef __int128 kll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 50505, P = 1e9 + 7;
const ll inf = 1e18;

int n, m, q, pos;
int val[N], pw[N];
int sum[N], pp[N];
int ne[N];
kll dp[N][22];
char s[N];

int calc(char c) {
	if(c == '?') return 0;
	return c - '0';
}

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) { return 1ll * a * b % P; }
int sub(int a, int b) {
	if((a -= b) < 0) a += P;
	return a;
}
int subarr(int l, int r) {
	return sub(sum[r], sum[l - 1]);
}

void work() {
	ll k; cin >> k;
	int ans = sum[pos - 1], v = val[pos - 1], _ = v ? (m - v) : 0;
	if(dp[pos][_] < k) {
		cout << -1 << endl;
		return ;
	}
	int i = pos;
	while(i <= n) {
		if(s[i] == '?') {
			rep(c, 0, 10) {
				int o = (v + c * pw[n - i]) % m;
				_ = o ? (m - o) : 0;
				if(dp[i + 1][_] >= k) {
					v = o;
					ans = add(ans, mul(c, pp[n - i]));
					break;
				} else {
					k -= dp[i + 1][_];
				}
			}
			++i;
		} else {
			ans = add(ans, subarr(i, ne[i] - 1));
			v = (v + val[ne[i] - 1] - val[i - 1] + m) % m;
			i = ne[i];
		}
	}
	cout << ans << endl;
}

void solve() {
	cin >> n >> m >> q >> (s + 1);
	pw[0] = 1; rep(i, 1, n + 1) pw[i] = (pw[i - 1] * 10) % m;
	rep(i, 1, n + 1) {
		int c = calc(s[i]);
		val[i] = (val[i - 1] + c * pw[n - i]) % m;
		sum[i] = (sum[i - 1] + c * 1ll * pp[n - i]) % P;
	}
	rep(i, 0, n + 2) rep(j, 0, m) dp[i][j] = 0; dp[n + 1][0] = 1;
	pos = 1;
	per(i, 1, n + 1) {
		rep(j, 0, m) if(dp[i + 1][j]) {
			if(s[i] == '?') {
				rep(c, 0, 10) {
					dp[i][(j + pw[n - i] * c) % m] += dp[i + 1][j];
				}
			} else {
				int c = s[i] - '0';
				dp[i][(j + pw[n - i] * c) % m] += dp[i + 1][j];
			}
		}
		int k = val[i - 1] ? (m - val[i - 1]) : 0;
		if(dp[i][k] >= inf) {
			pos = i; break;
		}
	}
	int pre = n + 1;
	per(i, 1, n + 1) {
		ne[i] = pre;
		if(s[i] == '?') pre = i;
	}
	while(q--) work();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	pp[0] = 1; rep(i, 1, N) pp[i] = pp[i - 1] * 10ll % P;
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
