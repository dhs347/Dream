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
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 2e3 + 8;
int jc[N * N], inv[N * N], dp[N][N], n, m, k;

int C(int n, int m) {
	if (n == m) return 1;
	if (m < 0 || m > n) return 0;
	return mul(jc[n], mul(inv[m], inv[n - m]));
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	jc[0] = 1; rep(i, 1, n * k + 1) jc[i] = mul(jc[i-1], i);
	inv[n * k] = kpow(jc[n * k], P - 2);
	per(i, 0, n * k) inv[i] = mul(inv[i+1], i+1);
	dp[0][0] = 1;
	rep(i, 0, n+1)
		rep(j, i, n+1) {
			if (j == 0) continue;
			dp[i][j] = add(i > 0 ? dp[i-1][j] : 0, mul(dp[i][j-1], C(j * k - (j - i) - 1, k - 2)));
			//dd(i), dd(j), de(dp[i][j]);
		}
	//de(dp[n][n]);
	if (k == 1) jc[n] = 1;
	cout << mul(dp[n][n], jc[n]);
	return 0;
}


