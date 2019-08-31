#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<ll, ll> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e5 + 100;
int T;
ll n, x, ans;
pii a[N];

bool cmp(pii a, pii b) {
	return 1ll * a.fi * b.se < 1ll * b.fi * a.se;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 1, T+1) {
		cin >> n;
		rep(i, 1, n+1) {
			cin >> x >> a[i].se;
			rep(j, (int) sqrt(x * 2), 10000000) if (j * (j + 1) / 2 >= x) {
				a[i].fi = j; break;
			}
		}
		ans = 0;
		sort(a+1, a+n+1, cmp);
		per(i, 1, n) a[i].se += a[i+1].se;
		rep(i, 1, n+1) ans += a[i].fi * a[i].se;
		cout << "Case #" << cas << ": " << ans << endl;
	}
	return 0;
}
