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
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;


const int N = 2e5 + 7;
ll ans1, ans2, ans3, w[N];
vi V;
ll a[N], b[N], c[N], d[N], nn, n, m;

void add(int p, int c) {
	if (p <= 0) return;
	for ( ; p <= nn; p += p & -p) w[p] += c;
}

ll Qry(int p) {
	ll r = 0;
	for ( ; p ; p -= p & -p) r += w[p];
	return r;
}

ll qry(int l, int r) {
	return Qry(r) - Qry(l - 1);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n+1) {
		cin >> a[i] >> b[i];
		V.pb(a[i]);
	}
	rep(i, 1, m+1) {
		cin >> c[i] >> d[i];
		V.pb(c[i]);
	}
	sort(all(V));
	V.erase(unique(all(V)),V.end());
	rep(i, 1, n+1) a[i] = lower_bound(all(V), a[i]) - V.begin() + 1;
	rep(i, 1, m+1) c[i] = lower_bound(all(V), c[i]) - V.begin() + 1;
	nn = sz(V);
	rep(i, 1, m+1) {
		add(c[i], d[i]);
	}
	rep(i, 1, n+1) {
		ans1 += qry(1, a[i]-1) * b[i];
		ans2 += qry(a[i], a[i]) * b[i];
		ans3 += qry(a[i]+1, sz(V)) * b[i];
	}
	cout << ans1 << " " << ans2 << " " << ans3 << endl;
	return 0;
}
