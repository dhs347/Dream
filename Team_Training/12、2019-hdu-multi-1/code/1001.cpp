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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 998244353;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 105;
int f[2][N][N][N], T, n, m, l, r, t, ans, o;
vector<pii> lim[N];

void upd(int &a, int b) { a = add(a, b);}

bool check(int a, int b, int c, int d) {
	for (auto u : lim[a]) {
		int cnt = 1;
		if (u.fi <= b) cnt++;
		if (u.fi <= c) cnt++;
		if (u.fi <= d) cnt++;
		if (cnt != u.se) return 0;
	}
	return 1;
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) lim[i].clear();
		rep(i, 1, m+1) {
			cin >> l >> r >> t;
			lim[r].pb(mp(l, t));
		}
		memset(f, 0, sizeof(f));
		f[0][0][0][0] = 1; ans = 0; o = 0;
		rep(i, 0, n) {
			memset(f[o ^ 1], 0, sizeof(f[o ^ 1]));
			per(j, 0, i+1)
				rep(k, 0, j+1)
					per(l, 0, k+1) {
						int t = f[o][j][k][l];
						if (!t) continue;
						if (check(i+1, j, k, l)) upd(f[o ^ 1][j][k][l], t);
						if (check(i+1, i, k, l)) upd(f[o ^ 1][i][k][l], t); 
						if (check(i+1, i, j, l)) upd(f[o ^ 1][i][j][l], t); 
						if (check(i+1, i, j, k)) upd(f[o ^ 1][i][j][k], t);
					} 
			o ^= 1;
		}
		per(j, 0, n+1)
			per(k, 0, j+1)
				per(l, 0, k+1) ans = add(ans, f[o][j][k][l]);
		cout << ans << endl;
	} 
	return 0;
}

