#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i++)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << " "
#define dd(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

struct ST{
	static const int N = 1e5 + 10;
	pii a[20][N];int  lg[N];
	void bud(int *v, int n) {
		rep(i, 2, n+1) lg[i] = lg[i >> 1] + 1;
		rep(i, 0, n) a[0][i] = mp(v[i], i);
		rep(i, 1, lg[n] + 1) rep(j, 0, n - (1 << i) + 1) {
			a[i][j] = min(a[i-1][j], a[i-1][j + (1 << i >> 1)]);
		}
	}
	pii qry(int l, int r) {
		if (l > r) swap(l, r);
		int i = lg[r - l + 1];
		return min(a[i][l], a[i][r + 1 - (1 << i)]);
	}
} st1, st2;

bool check(int l, int r) {
	if (l >= r) return 1;
	//dd(l);de(r);
	int p1 = st1.qry(l, r).se;
	int p2 = st2.qry(l, r).se;
	if (p1 != p2) return 0;
	return check(l, p1-1) & check(p1+1, r);
}

const int N = 1e5 + 10;
int l, r, n, a[N], b[N], ans, mid;

int main() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	while (cin >> n) {
		rep(i, 0, n) cin >> a[i];
		rep(i, 0, n) cin >> b[i];
		st1.bud(a, n);
		st2.bud(b, n);
		l = 0; r = n - 1;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (check(0, mid)) {
				l = mid + 1;
				ans = mid;
			}else r = mid - 1;
		}
		cout << ans + 1 << endl;
	}
	return 0;
}
