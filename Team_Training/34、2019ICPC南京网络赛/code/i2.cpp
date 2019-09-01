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
vector<pii> ch;
ll ans[N];

ll det(pii o, pii a, pii b) {
	a.fi -= o.fi, a.se -= o.se;
	b.fi -= o.fi, b.se -= o.se;
	return 1ll * a.fi * b.se - 1ll * a.se * b.fi;
}
void push(int x) {
	pii p = pii(x, t[x]);
	while(sz(ch) > 1 && det(p, ch.back(), ch[sz(ch) - 2]) >= 0) ch.pop_back();
	ch.pb(p);
}
bool check(pii i, pii j, int x) {
	assert(i.fi < j.fi);
	return i.se - j.se >= (i.fi - j.fi) * 1ll * x;
}
ll calc(int x) {
	int n = sz(ch), l = 1, r = n - 1, ans = 0;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(ch[mid], ch[mid - 1], x)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	int i = ch[ans].fi;
	return t[i] + (::n - i + 1) * 1ll * x;
}

void solve() {
	rep(i, 1, n + 1) cin >> t[i];
	sort(t + 1, t + 1 + n);
	ch.clear(); ch.pb(pii(n, t[n]));
	int p = n;
	per(i, 1, y + 1) {
		while(p > 1) {
			if(calc(i) <= t[p - 1] + y) push(--p);
			else break;
		}
		ans[i] = min(calc(i), t[p] + (ll)y);
	}
	rep(i, 1, y + 1) cout << ans[i] << " \n"[i == y];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n >> y) solve();
	return 0;
}
