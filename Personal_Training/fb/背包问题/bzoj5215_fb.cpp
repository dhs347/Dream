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
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e7 + 8, M = 1e6 + 7;
int jc[N], inv[N], n, m, k, S, f[M], g[M], a[M], ans;

int C(int n, int m) {
	if (m < 0 || m > n) return 0;
	return mul(jc[n], mul(inv[m], inv[n - m]));
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m >> k;
	jc[0] = 1; rep(i, 1, n+k+1) jc[i] = mul(jc[i-1], i);
	inv[n + k] = kpow(jc[n + k], P - 2); per(i, 0, n + k) inv[i]  = mul(inv[i+1], i + 1); 
	rep(i, 1, m+1) cin >> a[i], S += a[i];
	f[0] = 1;
	rep(i, 1, m+1) {
		g[0] = f[0]; rep(j, 1, S+1) g[j] = add(f[j], g[j-1]);
		per(j, 0, S+1) f[j] = add(g[j], - (j - a[i] - 1 >= 0 ? g[j - a[i] - 1] : 0));
	} 
	rep(i, 0, S+1) {
		if (i > k) break;
		if (n - m > 0) ans = add(ans, mul(f[i], C(k - i + n - m - 1, n - m - 1)));
		else if (i == k) ans = add(ans, f[i]);
	}
	cout << ans << endl;
	return 0;
}


