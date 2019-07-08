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
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e3+ 6;
int n, m, k;

ll b[N], cal[N][N], a[N], f[N][60];
vi p[N];

void add(int x) {
	for (; x <= n; x += x & -x) a[x]++;
}

int qry(int x) {
	int res = 0;
	for (; x; x -= x & -x) res += a[x];
	return res;
}

int main() {
	freopen("flight.in", "r", stdin);
	freopen("flight.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> k;
	rep(i, 1, n+1) cin >> b[i], p[b[i]].pb(i);
	rep(i, 1, m+1) {
		memset(a, 0, sizeof(a));
		rep(j, i, m+1) {
			cal[i][j] = cal[i][j-1];
			for (auto v : p[j]) cal[i][j] += qry(v);
			for (auto v : p[j]) add(v);
		}
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	rep(i, 1, m+1) rep(j, 1, k+1) rep(l, 0, i) f[i][j] = min(f[i][j], f[l][j-1] + cal[l+1][i]);
	cout << f[m][k] << endl;
	return 0;
}
