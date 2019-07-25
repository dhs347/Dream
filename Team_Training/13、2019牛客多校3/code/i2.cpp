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
	ans[1] = x, ans[2] = y; a[n + 3] = a[n + 2];
	rep(i, 3, n + 3) {
		if(x < y) {
			if(a[i] == x) {
				ans[i] = max(0, min(a[i + 1], a[i]));
			} else if(a[i] == y) {	
				ans[i] = min(inf, max(a[i], a[i + 1]));
		} else if(x < a[i] && a[i] < y) {
				ans[i] = a[i];
			} else {
				return 0;
			}
		} else if(x == y) {
			if(a[i] != x) return 0;
			ans[i] = a[i+1];
		} else {
			if(a[i] == x) {
				ans[i] = min(inf, max(a[i], a[i + 1]));
			} else if(a[i] == y) {
				ans[i] = max(0, min(a[i + 1], a[i]));
			} else if(y < a[i] && a[i] < x) {
				ans[i] = a[i];
			} else {
				return 0;
			}
		}
		x = y, y = ans[i];
	}
	return 1;
}

bool solve() {
	cin >> n;
	n -= 2;
	rep(i, 3, n + 3) cin >> a[i];
	vi vec;
	vec.pb(0), vec.pb(inf);
	rep(i, 1, min(3, n) + 1) vec.pb(a[i + 2]);
	rep(i, 0, sz(vec)) rep(j, 0, sz(vec)) if(i != j) if(check(vec[i], vec[j])) return 1;
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
