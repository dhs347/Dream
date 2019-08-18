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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef pair<ll, ll> pii;
typedef vector<int> vi;

const int N = 10005;
const ll inf = pw(61);
pii a[N], h[N];
ll w[N], s[N], f[N], tmp[N];
int n, k;

bool check(pii a, pii b, pii c) {
	return (__int128) (b.se - a.se) * (c.fi - b.fi) <
	(__int128) (c.se - b.se) * (b.fi - a.fi);
}

bool check2(pii a, pii b, ll t) {
	return (__int128) t * (b.fi - a.fi) < b.se - a.se;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n+1) {
		cin >> a[i].se >> a[i].fi;
	}
	sort(a+1, a+n+1);
	reverse(a+1, a+n+1);
	rep(i, 1, n+1) s[i] = s[i-1] + a[i].fi * a[i].se;
	rep(i, 1, n+1) w[i] = w[i-1] + a[i].se;
	rep(i, 0, n+1) f[i] = inf;
	rep(i, 1, n+1) tmp[i] = inf;
	rep(t, 0, k) {
		int l = 0, r = 0;
		rep(i, 1, n+1) {
			auto p =  mp(w[i-1], tmp[i-1] - s[i-1]);
			while (r - l >= 2 && !check(h[r-2], h[r-1], p)) r--;
			h[r++] = p;
			while (r - l >= 1 && !check2(h[l], h[l+1], -a[i].fi)) l++;
			//dd(i), dd(h[l].se), dd(s[i]), dd(a[i].fi);
			f[i] = s[i] + h[l].se - a[i].fi * (w[i] - h[l].fi);
		}
		rep(i, 0, n+1) tmp[i] = f[i];
	}
	cout << f[n] << endl;
	return 0;
}
