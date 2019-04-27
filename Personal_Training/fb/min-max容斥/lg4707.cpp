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
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 2e4 + 7;
int f[2][N][30], p[N], n, k, m, w, jc[N], inv[N], o, ans;

//int c(int n, int m) {
//	return mul(jc[n], mul(inv[n - m], inv[m]));
//}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k >> m;
	rep(i, 1, n+1) cin >> p[i];
	k = n - k + 1;
	//w = n - k;
	f[0][0][0] = 1;
	//jc[0] = 1; rep(i, 1, 10000+1) jc[i] = mul(jc[i-1], i);
	//inv[10000] = kpow(jc[10000], P - 2); per(i, 0, 10000) inv[i] = mul(inv[i+1], i+1);
	/*rep(i, 1, n+1) {
		o ^= 1;
		rep(j, 0, m+1) rep(l, 0, w+1) f[o][j][l] = f[o ^ 1][j][l];
		rep(j, 0, m+1) rep(l, 0, w+1) {
			int &t = f[o][j + p[i]][l + 1];
			t = add(t, f[o ^ 1][j][l]);
		}
	}*/
	rep(i, 1, n+1) {
		o ^= 1;
		rep(j, 0, m+1) rep(l, 0, k+1) f[o][j][l] = f[o ^ 1][j][l];
		rep(j, 0, m+1) rep(l, 1, k+1) {
			int &t = f[o][j + p[i]][l];
			t = add(t, f[o ^ 1][j][l - 1] - f[o ^ 1][j][l]);
		}
	}
	rep(j, 0, m+1) {
		int t = kpow(j, P - 2);
		//rep(l, 0, w+1) {		
		//if ((n - l + k + 1) & 1) ans = add(ans, mul(mul(c(n - l - 1, k - 1), f[o][j][l]), mul(m, t)));
		//	else ans = add(ans, -mul(mul(c(n - l - 1, k - 1), f[o][j][l]), mul(m, t)));
		ans = add(ans, mul(f[o][j][k], mul(m, t)));
	}
	cout << ans << endl;
	return 0;
}


