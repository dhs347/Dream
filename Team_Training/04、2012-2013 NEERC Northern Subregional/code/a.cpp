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
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, ans, s, now, d;

int main() {
	freopen("aztec.in", "r", stdin);
	freopen("aztec.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	s = 0;
	now = 1;
	d = 4;
	rep(i, 1, n+1) {
		s += now;
		if (s <= n) ans = i;else break;
		now += d;
		d += 4;
	}
	cout << ans << endl;
	return 0;
}
