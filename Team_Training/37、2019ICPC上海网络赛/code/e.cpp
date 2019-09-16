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
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, ll b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 3e5 + 7;
int T, m, M, jc[N], inv[N], ans;
ll n;

int C(int n, int m) {
	if (m < 0 || m > n) return 0;
	return mul(jc[n], mul(inv[n - m], inv[m]));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	jc[0] = 1; rep(i, 1, N) jc[i] = mul(jc[i-1], i);
	inv[N-1] = kpow(jc[N-1], P - 2); per(i, 0, N-1) inv[i] = mul(inv[i+1], i+1);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		M = m / 2; ans = 0;
		rep(k, 0, M+1) ans = add(ans, mul(C(M, k), kpow(m - 2 * k, n)));
		ans = mul(ans, kpow(kpow(2, M), P - 2));
		cout << ans << endl;
	}
	return 0;
}


