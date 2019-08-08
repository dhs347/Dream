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

ll f(ll x) {
	vi v;
	while(x) {
		v.pb(x % 10);
		x /= 10;
	}
	x = 0;
	rep(i, 0, sz(v)) x = x * 10 + v[i];
	return x;
}

void solve() {
	ll a, b;
	cin >> a >> b;
	cout << f(f(a) + f(b)) << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
