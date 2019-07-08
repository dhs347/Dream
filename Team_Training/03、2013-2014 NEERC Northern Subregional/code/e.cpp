#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	freopen("energy.in", "r", stdin);
	freopen("energy.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; string s;
	cin >> n >> s;
	int m = 0;
	int cnt[3] = {0};
	ll ans = 0;
	rep(i, 0, sz(s)) {
		if(s[i] == '1') {
			if(n == m && cnt[2]) --cnt[2], m -= 2;
			if(n != m) ++cnt[1], ++m;
		} else {
			if(n - m >= 2) ++cnt[2], m += 2;
		}
		ans += cnt[1] + cnt[2];
	}
	cout << ans << endl;
	return 0;
}
