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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int P = 1e9 + 7;

int kpow(int a, ll b) {
	int r = 1;
	while(b) {
		if(b & 1) r = r * 1ll * a % P;
		a = a * 1ll * a % P;
		b >>= 1;
	}
	return r;
}

void solve() {
	ll n, l, r, k;
	cin >> n >> l >> r >> k;
	ll c = n - l - r + 2;
	if(c >= 0) {
		if(c == k) {
			cout << 1 << endl;
		} else if(c > k) {
			cout << (k + 1) % P << endl;
		} else {
			ll t = k - c;
			ll mi = min(l - 1, r - 1);
			ll ans = min(t, mi);
			cout << kpow(2, ans) << endl;
		}
	} else {
		ll ans = k;
		ans = min(ans, n - (l - 1));
		ans = min(ans, n - (r - 1));
		cout << kpow(2, ans) << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
