#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<ll, ll> pii;
typedef vector<int> vi;

const int N = 1e5  + 7;
ll mi, ma, t1, t2, t3, tmp, ansl, ansr, T, n, m, a[N], b[N];
pii t;
ll cal(ll l, ll r) {
	if (l > r) swap(l, r);
	return (l + r) * (r - l + 1) / 2;
}

pii solve(ll len, ll l, ll r) {
	if (l + len + 1 < r) return mp(-1, 1);
	t1 = t2 = t3 = 0;
	t3 = r - l; tmp = len + 1 - t3;
	//de(tmp);
	t3 += tmp / 2;
	t1 += tmp / 2;
	t2 = tmp & 1;
	ma = cal(l, l + t3) + t2 * (l + t3);
	if (t1 > 0) ma += cal(l + t3 - 1, r);
	if (l - t1 < 0) {
		t2 += 2 * (t1 - l);
		t3 -= t1 - l;
		t1 = l;
	}
	mi = cal(l, l - t1) + t2 * (l - t1);
	if (t3 > 0) mi += cal(l - t1 + 1, r);
	return mp(mi - l - r, ma - l - r);
}

pii solve2(ll len, ll r) {
	ma = cal(r, r + len);
	mi = cal(r, max(0ll, r - len));
	return mp(mi - r, ma - r);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T >> n >> m;
	rep(i, 1, m+1) {
		cin >> a[i] >> b[i];
		ansl += b[i];
		ansr += b[i];
	}
	rep(i, 2, m+1) {
		pii t = solve(a[i] - a[i-1] - 1, min(b[i-1], b[i]), max(b[i-1], b[i]));
		if (t.fi == -1) {
			cout << "No";
			return 0;
		}
		ansl += t.fi;
		ansr += t.se;
	}
	t = solve2(a[1] - 1, b[1]);
	ansl += t.fi; ansr += t.se;
	t = solve2(n - a[m], b[m]);
	ansl += t.fi; ansr += t.se;
	//de(ansl);de(ansr);
	if (ansl <= T && T <= ansr) cout << "Yes";else cout << "No";
	return 0;
}
