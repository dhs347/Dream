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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1010;

int n, d;
int a[N][11], b[N][11], cur[N];

bool cmp(int i, int j) {
	rep(k, 1, d + 1) if(b[i][k] != b[j][k]) return b[i][k] < b[j][k];
	return 0;
}
bool equ(int i, int j) {
	rep(k, 1, d + 1) if(b[i][k] != b[j][k]) return 0;
	return 1;
}
vi vec;
int main() {
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> d;
	rep(i, 1, n + 1) rep(j, 1, d + 1) cin >> a[i][j];
	int ans = 1; vec.pb(1);
	rep(i, 1, n + 1) {
		rep(j, 1, n + 1) if(i != j) {
			int k = j - (j > i);
			int t1[11];
			int fi = 0;
			rep(t, 1, d + 1) {
				t1[t] = a[i][t], b[k][t] = a[j][t];
				if(a[i][t] && !fi) fi = t;
			}
			rep(t, 1, d + 1) t1[t] *= a[j][fi], b[k][t] *= a[i][fi];
			int g = 0;
			rep(t, 1, d + 1) b[k][t] -= t1[t], g = __gcd(g, b[k][t]);
			if(g) rep(t, 1, d + 1) b[k][t] /= g;
			fi = 0;
			rep(t, 1, d + 1) if(b[k][t] && !fi) fi = t;
			if(b[k][fi] < 0) rep(t, 1, d + 1) b[k][t] = -b[k][t];
		}
		rep(i, 1, n) cur[i] = i;
		sort(cur + 1, cur + n, cmp);
		vi z, cnt;
		rep(j, 1, n) {
			int rel = cur[j] + (cur[j] >= i);
			if(j == 1 || !equ(cur[j - 1], cur[j])) cnt.clear();
			cnt.pb(rel);
			if(equ(cur[j], 0)) {
				z.pb(rel);
				if(1 + sz(z) > ans) {
					ans = 1 + sz(z);
					vec = z;
					vec.pb(i);
				}
			} else {
				if(1 + sz(z) + sz(cnt) > ans) {
					ans = 1 + sz(z) + sz(cnt);
					vec = z; vec.pb(i);
					vec.insert(vec.end(), all(cnt));
				}
			}
		}
	}
	cout << ans << endl;
	rep(i, 0, sz(vec)) cout << vec[i] << " \n"[i == ans - 1];
	return 0;
}
