#include<bits/stdc++.h>
#pragma GCC optimize("Ofast") 
#pragma GCC optimize("unroll-loops") 
#pragma GCC target("sse2")
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
//----

const int N = 1e7 + 7;
int n, nn, m, a[N / 4], b[N * 3], c[N * 6], l[N / 9], r[N / 9], pre, sm[N / 4], pm[N / 4], pos[N / 4], L, R;
vector<pii> V;

void upd(int &L, int &R, int l, int r) {
	if (R + 1 == l) R = r;
	else {
		if (L >= 0) V.pb(mp(L, R));
		L = l; R = r;
	}
}

void add(int p) {
	if (p <= 0) return;
	c[p]++;
}

int qry(int p) {
	if (p <= 0) return 0;
	int res = 0;
	for ( ; p > 0; p -= lb(p)) res += c[p];
	return res;
}

ll solve(int n) {
	ll res = 0, now = 0; int pre = 0;
	rep(i, 1, n+1) b[i] += b[i-1];
	int ma = *max_element(b, b+n+1);
	int mi = *min_element(b, b+n+1);
    ma++;mi--; 
	nn = ma - mi + 5;
	memset(c, 0, sizeof(int) * (nn + 1));
	add(-mi);
	rep(i, 1, n+1) {
		if (b[i] > pre) res += (now += c[pre - mi]);
		else res += (now -= c[pre - mi - 1]);
		add(b[i] - mi);
		pre = b[i];
	}
	return res;
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 0, n) {
		cin >> l[i] >> r[i];
		if (l[i] > 0) a[++m] = -(l[i] - pre);
		a[++m] = r[i] - l[i] + 1;
		pre = r[i] + 1; 
	}
	a[++m] = -(1000000000 - pre);
	rep(i, 1, m+1) pos[i] = pos[i-1] + abs(a[i-1]);
	rep(i, 1, m+1) {
		pm[i] = pm[i-1] + a[i];
		if (pm[i] < 0) pm[i] = 0;
	}
	per(i, 1, m+1) {
		sm[i] = sm[i+1] + a[i];
		if (sm[i] < 0) sm[i] = 0;
	}
	L = R = -pw(30);
	rep(i, 1, m+1) {
		if (a[i] > 0) {
			upd(L, R, pos[i], pos[i] + a[i] - 1);
 		}else {
			if (pm[i-1] + sm[i+1] + a[i] > 0) {
				upd(L, R, pos[i], pos[i] + abs(a[i]) - 1);
			}else {
				if (pm[i-1] > 1) upd(L, R, pos[i], pos[i] + pm[i-1] - 2);
				if (sm[i+1] > 1) upd(L, R, pos[i] + abs(a[i]) - 1 - sm[i+1] + 2, pos[i] + abs(a[i]) - 1);
			}
		}
	}
	if (L >= 0) V.pb(mp(L, R)); 
	int p = 0;
	ll ans = 0;
	for (auto v : V) {
		memset(b+1, -1, sizeof(int) * (v.se - v.fi + 1));
		while (p < n && r[p] <= v.se) {
			fill_n(b + l[p] - v.fi + 1, r[p] - l[p] + 1, 1);
			p++;
		}
		ans += solve(v.se - v.fi + 1);
	}
	cout << ans << endl;
	return 0;
}


