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
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 1e6 + 2;

int n, y, t[N];
vi ch;
ll ans[N];

ll det(pii o, pii a, pii b) {
	a.fi -= o.fi, a.se -= o.se;
	b.fi -= o.fi, b.se -= o.se;
	return 1ll * a.fi * b.se - 1ll * a.se * b.fi;
}

void push(int i) {
	if(!i) return ;
	while(sz(ch) >= 2 && det(pii(t[i], i), pii(t[ch.back()], ch.back()), pii(t[ch[sz(ch) - 2]], ch[sz(ch) - 2])) >= 0) ch.pop_back();
	ch.pb(i);
}
ll cs(int i) {
	if(!i) return 0;
	return t[i] + y;
}
ll cx() {
	// ch should reverse
	int n = sz(ch), l = 0, r = n - 2, ans = n - 1;
	while(l <= r) {
		int mid = l + r >> 1, i = mid, j = i + 1;
		i = ch[n - 1 - i], j = ch[n - 1 - j];
		assert(i < j);

	}
}

void solve() {
	rep(i, 1, n + 1) cin >> t[i];
	sort(t + 1, t + 1 + n);
	ch.clear(); ch.pb(n);
	int p = n;
	per(i, 1, y + 1) {
		ll res = -1;
		while(p) {
			ll as = cs(p - 1);
			ll ax = cx();
			if(ax <= as) {
				push(--p);
				res = as;
			} else {
				res = min(ax, res);
			}
		}
		assert(~res);
		ans[i] = res;
	}
	rep(i, 1, y + 1) cout << ans[i] << " \n"[i == y];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n >> y) solve();
	return 0;
}
