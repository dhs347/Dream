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
typedef long double db;
typedef pair<db, db> pii;
typedef vector<int> vi;
typedef long long ll;
const db inf = 1e17;
const int N = 1e5 + 7;

int n, q, c[N], m, o, x, l2[N], rr[N];
db a[N], d[N], f[2][N];
pii h[N];



bool check(pii a, pii b, pii c) {
	return (db)(b.se - a.se)/ (b.fi - a.fi) < (db) (c.se - b.se) / (c.fi - b.fi);
}

db kk(pii a, pii b) {
	return (db) (b.se - a.se) / (b.fi - a.fi);
}

void upd(db &x, db y) {
	x = min(x, y);
}

int get(int l, int r, db k, int o) {
	int l1 = l, r1 = r-2;
	int ans = h[r-1].fi;
	while (l1 <= r1) {
		int mid = l1 + r1 >> 1;
		db t = kk(h[mid], h[mid+1]);
		if ((t < k) ^ o) ans = h[mid].fi, r1 = mid - 1;
		else l1 = mid + 1;
	}
	return ans;
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> q;
	m = 20000;
	rep(i, 1, n+1) cin >> a[i] >> d[i] >> c[i];
	rep(i, 1, m+1) f[o][i] = inf;
	rep(i, 0, m+1) f[o^1][i] = inf;
	rep(i, 1, n+1) {
		for (int j = 0; j <= m; j += c[i]) {
			int l = 0, r = 0;
			rep(k, j, min(j+c[i], m)+1) {
				auto p = mp(k, d[i] * k * k / 2 - f[o][k]);
				while (r - l >= 2 && check(h[r-2], h[r-1], p)) r--;
				h[r++] = p;
				int id = get(l, r, k * d[i] - a[i] - d[i] / 2, 0);	
				upd(f[o^1][k], f[o][id] - d[i] / 2 * (k - id) * (k - id) + (a[i] + d[i] / 2) * (k - id));
			}
			l = 0; r = 0;
			per(k, max(0, j - c[i]), j+1) {
				auto p = mp(k, d[i] * k * k / 2 - f[o][k]);
				while (r - l >= 2 && !check(h[r-2], h[r-1], p)) r--;
				h[r++] = p;
				int id = get(l, r, (k + c[i]) * d[i] - a[i] - d[i] / 2, 1);
				if (k + c[i] <= m) {
					upd(f[o^1][k + c[i]], f[o][id] - d[i] / 2 * (k + c[i]- id) * (k +c[i] - id) + (a[i] + d[i]/ 2) * (k + c[i] - id));
				}
			} 
		}
		rep(j, 0, m+1) f[o][j] = inf;
		o ^= 1;
	}  
	rep(i, 1, q+1) {
		cin >> x;
		cout << (ll)round(f[o][x]) << endl;
	}
	return 0;
}
