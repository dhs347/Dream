#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 6;
int ansl[2], ansr[2], ansd[2], d1, s1, s2, cnt, cnt2, d2, p[2][N], n;
pii a[2][N];
bool vis[N];
bool solve(int d1, int s, int o) {
	cnt = 0;vi tmp;
	if (d1 == 0) return 0;
	memset(vis, 0, sizeof(vis));
	rep(i, 1, n+1) {
		if (a[o][i].fi == cnt * d1 + s) {
			vis[p[o][i]] = 1;
			cnt++;
		}
	}
	rep(i, 1, n+1) if (!vis[i]) {
		tmp.pb(a[o ^ 1][i].fi);
	}
	if (sz(tmp) == 0) {
	//	de(a[o ^ 1][1]);
	//	de(a[o ^ 1][n]);
		if (a[o ^ 1][1].fi == a[o ^ 1][n].fi) {
			int t = a[o ^ 1][1].fi;
			if (t + 1 > 1000000000) t = t - 1;else t = t + 1;
			ansl[o ^ 1] = ansr[o ^ 1] = t; ansd[o ^ 1] = 1;	
		}else {
			ansl[o ^ 1] = ansr[o ^ 1] = a[o ^ 1][1].fi; ansd[o ^ 1] = 1;
		}
		ansl[o] = s; ansr[o] = s + (cnt - 1) * d1; ansd[o] = d1;
		return 1;
	}
	else if (sz(tmp) == 1) {
		//de(o);de(d1);
		//rep(i, 1,n+1) dd(vis[i]);
		ansl[o ^ 1] = ansr[o ^ 1] = tmp[0]; ansd[o ^ 1] = 1;
		ansl[o] = s; ansr[o] = s + (cnt - 1) * d1; ansd[o] = d1;
		return 1;
	}else {
		d2 = 0;
		rep(i, 1, sz(tmp)) d2 = __gcd(d2, tmp[i] - tmp[i-1]);
		s2 = tmp[0]; cnt2 = 0;
		rep(i, 1, n+1) if (a[o^1][i].fi == cnt2 * d2 + s2) vis[i] = 1, cnt2++;
		rep(i, 1, n+1) if (!vis[i]) return 0;
		ansl[o ^ 1] = s2; ansr[o ^ 1] = s2 + (cnt2 - 1) * d2; ansd[o ^ 1] = d2;
		ansl[o] = s; ansr[o] = s + (cnt - 1) * d1; ansd[o] = d1;
		return 1;
	}
}

int main() {
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> a[0][i].fi >> a[1][i].fi;
		a[0][i].se = a[1][i].se = i;
	}
	rep(i, 0, 2) sort(a[i]+1, a[i]+n+1);
	rep(i, 1, n+1) {
		p[0][a[0][i].se] = i;
	}
	//rep(i, 1, n+1) dd(p[0][i]);
	rep(i, 1, n+1) {
		p[1][i] = p[0][a[1][i].se];
	}
	rep(i, 1, n+1) p[0][p[1][i]] = i;
	//rep(i, 1, n+1) dd(p[0][i]);
	rep(i, 1, 4) rep(j, i+1, 4) rep(k, 0, 2){
		int ok = solve(a[k][j].fi - a[k][i].fi, a[k][i].fi, k);
		if (ok) {
			rep(l, 0, 2) cout << ansl[l] << " " <<  ansr[l] << " " << ansd[l] << " \n"[l == 1];
			return 0;
		}
	} 
	return 0;
}
