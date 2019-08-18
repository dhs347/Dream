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

const int N = 505050;

int n, m, a[N], b[N], ma, mb;
pii cha[N], chb[N];

ll det(pii o, pii a, pii b) {
	a.fi -= o.fi, a.se -= o.se;
	b.fi -= o.fi, b.se -= o.se;
	ll ans = a.fi * 1ll * b.se - a.se * 1ll * b.fi;
	return ans;
}

void gao(int a[], int n, pii ch[], int &m) {
	m = 0;
	rep(i, 0, n + 1) {
		while(m >= 2 && det(ch[m - 1], mp(i, a[i]), ch[m]) >= 0) --m;
		ch[++m] = mp(i, a[i]);
	}
}

int main() {
	freopen("iron.in", "r", stdin);
	freopen("iron.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 0, n + 1) cin >> a[i];
	rep(i, 0, m + 1) cin >> b[i];
	gao(a, n, cha, ma);
	gao(b, m, chb, mb);
	int p = 1, q = 1;
	ll ans = 0;
	while(p < ma && q < mb) {
		pii a = cha[p + 1], b = chb[q + 1];
		a.fi -= cha[p].fi, a.se -= cha[p].se;
		b.fi -= chb[q].fi, b.se -= chb[q].se;
		if(det(pii(0, 0), a, b) >= 0) {
			ans += chb[q].se * 1ll * (cha[p + 1].fi - cha[p].fi);
			++p;
		} else {
			ans += cha[p].se * 1ll * (chb[q + 1].fi - chb[q].fi);
			++q;
		}
	}
	ans += chb[mb].se * 1ll * (n - cha[p].fi);
	ans += cha[ma].se * 1ll * (m - chb[q].fi);
	cout << ans << endl;
	return 0;
}
