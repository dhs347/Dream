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

const int N = 222;

int n, dp[N], pre[N];
char s[N];

/*
void solve() {
	cin >> s;
	vi vec;
	int cnt = 0;
	if(s[0] == '1') vec.pb(0);
	rep(i, 0, sz(s)) {
		if(i == 0 || s[i] == s[i - 1]) ++cnt;
		if(i == sz(s) - 1 || s[i] != s[i + 1]) {
			vec.pb(cnt);
			cnt = 0;
		}
	}
	if(s[sz(s) - 1] == '0') vec.pb(0);
	int x = -1, y = 0;
	for(int i = 1; i < sz(vec); i += 2) {
		if(vec[i - 1] > x || (vec[i - 1] == x && vec[i] <= y)) {
		}
	}
}*/
bool check(int x, int y) {
	rep(d, 1, y - x + 1) {
		rep(i, x, y + 1) {
			int j = i + d;
			if(j > y) j = x + j - y - 1;
			if(s[i] != s[j]) {
				if(s[i] > s[j]) return 0;
				break;
			}
		}
	}
	return 1;
}
void solve() {
	cin >> (s + 1); n = strlen(s + 1);
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	rep(i, 1, n + 1) {
		rep(j, 0, i) if(dp[j] + 1 < dp[i] && check(j + 1, i)) {
			dp[i] = dp[j] + 1;
			pre[i] = j;
		}
	}
	vi vec;
	int now = n;
	while(now) {
		vec.pb(now);
		now = pre[now];
	}
	vec.pb(0);
	reverse(all(vec));
	rep(i, 1, sz(vec)) {
		rep(j, vec[i - 1] + 1, vec[i] + 1) cout << s[j];
		cout << " \n"[i == sz(vec) - 1];
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
