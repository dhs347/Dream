#include<bits/stdc++.h>
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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, d, p[N];
vi a[N];

bool cmp(vi a, vi b) {
	per(i, 0, d) if(a[i] != b[i]) {
		return a[i] < b[i];
	}
	return 0;
}

void solve(int l, int r, int dep) {
	if(!dep) return ;
	int pre = l;
	rep(i, l, r + 1) if(i == r || a[i][dep - 1] != a[i + 1][dep - 1]) {
		solve(pre, i, dep - 1);
		pre = i + 1; 
	}
	for(int i = r; a[i][dep - 1] > a[0][dep - 1] / 2; --i) {
		auto t = a[i]; t[dep - 1] = a[0][dep - 1] - t[dep - 1];
		auto j = lower_bound(a + 1, a + 1 + n, t, cmp) - a;
		swap(p[i], p[j]);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> n >> d;
	rep(i, 0, n + 1) {
		rep(j, 0, d) {
			int x; cin >> x;
			a[i].pb(x);
		}
		a[i].pb(i);
	}
	rep(j, 0, d) a[0][j] = 0;
	rep(i, 1, n + 1) rep(j, 0, d) a[0][j] = max(a[0][j], a[i][j]);
	sort(a + 1, a + 1 + n, cmp);
	rep(i, 1, n + 1) p[i] = i;
	solve(1, n, d);
	rep(i, 1, n + 1) cout << a[i][d] << " " << a[p[i]][d] << endl;
	return 0;
}

