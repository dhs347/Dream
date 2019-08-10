#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 1e5 + 7;
ll ans, n, a[N];
vi v[N];

ll cal(ll n) {
	return 1ll * (n + 1) * n / 2;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i], v[a[i]].pb(i);
	rep(i, 1, n+1) v[i].pb(0), v[i].pb(n+1), sort(all(v[i]));
	rep(i, 1, n+1) {
		ll t = cal(n);
		rep(j, 1, sz(v[i])) t -= cal(v[i][j] - v[i][j - 1] - 1);
		ans += t;
	}
	cout << ans << endl;
	return 0;
}
