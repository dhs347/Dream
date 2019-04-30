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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e6 + 7;
int jc[N], inv[N], pn[N], n, m, a, b, tmp, ans, M, pm[N];

int A(int n, int m) {
	if (m > n) return 0;
	return mul(jc[n], inv[n - m]);
}

int C(int n, int m) {
	if (m > n) return 0;
	return mul(jc[n], mul(inv[m], inv[n - m]));
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	M = 1e6;
	jc[0] = 1;rep(i, 1, M+1) jc[i] = mul(jc[i-1], i);
	inv[M] = kpow(jc[M], P - 2);
	per(i, 0, M) inv[i] = mul(inv[i+1], i+1);
	cin >> n >> m >> a >> b;
	pn[0] = 1; rep(i, 1, M+1) pn[i] = mul(pn[i-1], n);
	pm[0] = 1; rep(i, 1, M+1) pm[i] = mul(pm[i-1], m);
	rep(i, 0, n - 2 + 1) {
		tmp = mul(A(n - 2, i), C(m - 1, i));
		tmp = mul(tmp, pm[n - i - 2]);
		if (n - i - 3 >= 0) tmp = mul(tmp, mul(pn[n - i - 3], i + 2));
		ans = add(ans, tmp);
	}
	cout << ans << endl;
	return 0;
}


