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

const int N = 101010, inf = 1e9;

int n, a[N], ans[N];

bool check(int x, int y) {
	ans[1] = x, ans[2] = y;
	rep(i, 3, n + 3) {
		if(x < y) {
			if(a[i] == x) {
				ans[i] = 0;
			} else if(a[i] == y) {
				ans[i] = inf;
			} else if(x < a[i] && a[i] < y) {
				ans[i] = a[i];
			} else {
				return 0;
			}
		} else if(x == y) {
			if(a[i] != x) return 0;
			if(x == 0) ans[i] = inf;
			else ans[i] = 0;
		} else {
			if(a[i] == x) {
				ans[i] = inf;
			} else if(a[i] == y) {
				ans[i] = 0;
			} else if(y < a[i] && a[i] < x) {
				ans[i] = a[i];
			} else {
				return 0;
			}
		}
		x = y, y = ans[i];
		dd(i), de(ans[i]);
	}
	return 1;
}

bool solve() {
	cin >> n;
	n -= 2;
	rep(i, 3, n + 3) cin >> a[i];
	if(check(0, a[3])) return 1;
	if(check(0, inf)) return 1;
	if(check(a[3], 0)) return 1;
	if(check(a[3], inf)) return 1;
	if(check(inf, 0)) return 1;
	if(check(inf, a[3])) return 1;
	cout << -1 << endl;
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) {
		if(solve()) rep(i, 1, n + 3) cout << ans[i] << " \n"[i == n + 2];
	}
	return 0;
}
