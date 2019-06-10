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

const int N = 2e5 + 7;
int n, f[N], jc[N], inv[N], k, dp[N], K, ans, c, dp2[N], cc[200][200];

int C(int n, int m) {
	if (m < 0 || m > n) return 0;
	return mul(jc[n], mul(inv[m], inv[n - m]));
}

struct Min_25{ 
	// F(i) 要拆成多个完全积性函数的和 
	static const int N = 1e6 + 7;
	int Sqr, m, p[N], id1[N], id2[N], tot, cntp;
	int g[N], sp[N], h[N], n, w[N];
	bool isp[N];
	// f(p) = p ^ k 
	ll f(int p) { return 1;}
 
	// 要求的积性函数 F(p ^ e) 
	ll F(int p, int e) { return cc[e + c - 1][c - 1];}

	// 假设都是质数的完全积性函数前缀和去掉 f(1) 
	ll calc(ll n) { return (n - 1);}

	void prime(int n){
    	cntp = 0;isp[1] = 1;
    	rep(i, 2, n+1) {
        	if(!isp[i]) p[++cntp] = i;
        	for(int j = 1; j <= cntp && i * p[j] <= n; j++){
            	isp[i * p[j]] = 1;
            	if(i % p[j] == 0)break;
        	}
    	}
    	rep(i, 1, cntp+1) sp[i] = sp[i - 1] + f(p[i]);
    	p[++cntp] = INT_MAX;
	}
	
	int S(ll x, int y){
    	if(x <= 1 || p[y] > x) return 0;
    	int k = (x <= Sqr ? id1[x] : id2[n/x]);
		int ret = mul(c, (g[k] - sp[y-1])); // 质数的答案 
    	for(int i = y; i <= tot && 1ll * p[i] * p[i] <= x; i++){
        	ll t1 = p[i], t2 = 1ll * p[i] * p[i];
        	for(int e = 1; t2 <= x; e++, t1 = t2, t2 *= p[i]) {
    			if (F(p[i], e)) ret = add(ret, mul(S(x / t1, i + 1), F(p[i], e)));
				ret = add(ret, F(p[i], e + 1));// 合数的答案 
			}
		}
    	return ret;
	}
	
	void  solve(ll _n) {
		n = _n;if (n == 0) return;
		m = 0;Sqr = sqrt(n);
		tot = upper_bound(p + 1, p + cntp + 1, Sqr) - (p + 1);
		for(ll i = 1, j; i <= n; i = j + 1){
        	j = n / (n / i);
			w[++m] = n / i;
        	g[m] = calc(w[m]);
        	w[m] <= Sqr ? id1[w[m]] = m : id2[j] = m;
    	}
    	rep(j, 1, tot + 1)
        	for(int i = 1; i <= m && 1ll * p[j] * p[j] <= w[i]; i++){
				ll t = w[i] / p[j];
				int k = t <= Sqr ? id1[t] : id2[n / t]; 
        		g[i] -= f(p[j]) * (g[k] - sp[j - 1]);
			}
		for (c = 1; c <= K; c++) dp[c] = (S(n, 1) + 1) % P;
		return;
		//return S(n,1) + 1;
	}	
} _U;



int main() {
	freopen("a.in","r",stdin);
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	n = 100;
	jc[0] = 1; rep(i, 1, n+1) jc[i] = mul(jc[i-1], i);
	inv[n] = kpow(jc[n], P - 2); per(i, 0, n) inv[i] = mul(inv[i + 1], i + 1);
	rep(i, 0, 100) rep(j, 0, 100) cc[i][j] = C(i, j);
	_U.prime(1e5);
	while (cin >> n >> K) {
		dp[0] = 1;ans = 0;
		_U.solve(n);
		//for (c = 1; c <= K; c++) dp[c] = _U.solve(n) % P;//, dd(dp[c]), de(dp2[c]);
		//rep(i, 1, K+1) de(dp[i]); 
		rep(i, 0, K+1) if (i & 1) ans = add(ans, -mul(dp[K - i], C(K, i)));else ans = add(ans, mul(dp[K - i], C(K, i)));
		cout << ans << endl;
	}
	return 0;
}
