// TSPŒ Ã‚ 
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
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 55;
int n, m, a[N][N], g[N][N], f[11][1 << 11], S, ans;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n >> m) {
		vector<pii> V;
		rep(i, 0, n) rep(j, 0, m) {
			cin >> a[i][j];
			if (a[i][j] > 0 || (i == 0 && j == 0)) V.pb(mp(i, j));
		}
		n = sz(V);
		rep(i, 0, n) rep(j, 0, n) g[i][j] = abs(V[i].fi - V[j].fi) + abs(V[i].se - V[j].se);
		S = pw(n) - 1;
		memset(f, 0x3f, sizeof(f));
		f[0][S ^ 1] = 0;
		per(i, 0, S+1) rep(j, 0, n) if (f[j][i] < 10000000) {
			rep(k, 0, n) if (i & pw(k)) f[k][i ^ pw(k)] = min(f[k][i ^ pw(k)], f[j][i] + g[j][k]);
		}
		ans = pw(30);
		rep(i, 0, n) ans = min(ans, f[i][0] + g[i][0]);
		cout << ans << endl;
	}
	return 0;
}


