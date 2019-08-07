#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int len = 120, N = 20;
ll opy[N], ans, x[N], y[N], k[N], t[N], tt[N], n, m, T, opx[N];
vi VX, VY;

ll cal(int l, int r, int k) {
	int t1 = 0, t2 = 0;
	if (r - 1 >= k) t1 = (r - 1 - k) / len + 1;
	if (l - 1 >= k) t2 = (l - 1 - k) / len + 1;
	return t1 - t2;
}

ll solve(int xl, int xr, int yl, int yr) {
//	dd(xl), de(xr);
	rep(i, 1, n+1) {
		tt[i] = t[i];
		if (x[i] <= xl) tt[i] = tt[i] + x[i], opx[i] = 1;
		else tt[i] = tt[i] - x[i], opx[i] = -1, assert(x[i] >= xr);
		if (y[i] <= yl) tt[i] = tt[i] + y[i], opy[i] = 1;
		else tt[i] = tt[i] - y[i], opy[i] = -1, assert(y[i] >= yr);
		tt[i] = (tt[i] % k[i] + k[i]) % k[i];
	}
	ll res = 0;
	rep(i, 0, len)
		rep(j, 0, len) {
			bool ok = 1;
			rep(l, 1, n+1) {
				int tmp = i * opx[l] + j * opy[l];
				tmp = (tmp % k[l] + k[l]) % k[l];
				if (tmp != tt[l]) {
					ok  = 0;
					break;
				}
			}
			if (ok) {
				res += 1ll * cal(xl, xr, i) * cal(yl, yr, j);
			}
		}
	return res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		ans = 0;
		VX.clear();
		VY.clear();
		rep(i, 1, n+1) cin >> x[i] >> y[i] >> k[i] >> t[i], VX.pb(x[i]), VY.pb(y[i]);
		VX.pb(0);VX.pb(m+1);
		VY.pb(0);VY.pb(m+1);
		sort(all(VX)); 
		VX.erase(unique(all(VX)), VX.end());
		sort(all(VY));
		VY.erase(unique(all(VY)), VY.end());
		rep(i, 0, sz(VX) - 1) {
			rep(j, 0, sz(VY) - 1) {
				ans += solve(VX[i], VX[i+1], VY[j], VY[j+1]);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
