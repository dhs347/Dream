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

const int N = 205;
db f[2][N * 2][N], p[N], ans;
int n, l, k, a[N], d;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	cin >> n >> l >> k;
	rep(i, 1, n+1) cin >> p[i], p[i] /= 100;
	rep(i, 1, n+1) cin >> a[i];
	d = n; 
	int o = 0;
	f[0][min(n, k) + d][0] = 1;
	rep(i, 1, n+1) {
		o ^= 1;
		rep(j, 0, d + n + 1) rep(m, 0, l+1) f[o][j][m] = 0;
		rep(j, 0, d + n + 1) 
			rep(m, 0, l+1) {
				f[o][min(j + a[i], d + n)][min(l, m + 1)] += f[!o][j][m] * p[i];
				f[o][j][m] += f[!o][j][m] * (1 - p[i]);
			}
	}
	rep(i, d, d+n+1) ans += f[o][i][l];
	cout << ans << endl; 
	return 0;
}

