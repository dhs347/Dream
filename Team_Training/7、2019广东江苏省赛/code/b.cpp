#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 202020;

ll k, m, n, p;
ll a[N], b[N], c[N];

ll mul(ll a, ll b) {
	__int128 r = a;
	r *= b;
	r %= p;
	return r;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> k >> m >> n >> p) {
		rep(i, 1, k + 1) cin >> a[i];
		sort(a + 1, a + 1 + k);
		ll ans = 0;
		rep(i, 1, k + 1) a[i] %= p, a[i] += p, a[i] %= p;
		b[0] = c[0] = 1;
		rep(i, 1, m + 1) {
			b[i] = mul(b[i - 1], n) % p;
			c[i] = (c[i - 1] + b[i]) % p;
		}
		int pos = 0;
		rep(dep, 2, m + 1) {
			ll cnt = b[dep - 1], w = c[m - dep];
			while(cnt--) ans = (ans + mul(a[++pos], w)) % p;
		}
		cout << ans << endl;
		return 0;
	}
	return 0;
}
