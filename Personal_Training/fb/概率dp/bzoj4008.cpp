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

const int N = 505;
int n, T, r;
db f[N][N], p[N][N], d[N];

void dfs(int now, int r) {
	if (f[now][r] >= 0) return;
	db t = p[now][r];
	if (now == n) {
		f[now][r] = (1 - t) * d[now];
		return;
	}
	if (r == 0) {f[now][r] = 0;return;}
	dfs(now+1, r);
	dfs(now+1, r-1);
	f[now][r] = t * f[now+1][r] + (1 - t) * (f[now+1][r-1] + d[now]);
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(10);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> r;
		rep(i, 1, n+1) rep(j, 0, r+1) f[i][j] = -1;
		rep(i, 1, n+1) cin >> p[i][1] >> d[i], p[i][1] = 1 - p[i][1];
		rep(i, 1, n+1) {p[i][0] = 1; rep(j, 2, r+1) p[i][j] = p[i][j-1] * p[i][1];}
		dfs(1, r);
		cout << f[1][r] << endl; 
	}
	return 0;
}

