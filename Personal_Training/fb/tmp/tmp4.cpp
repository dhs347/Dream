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
const int P = 998244353;
//int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

namespace _lo {
	int T, k;
	const int K = 10, P = 998244353; // e1+e2 <= K
	static int inv[K + 2], C[K + 2][K + 2], B[K + 1]; // ²®Å¬ÀûÊý 
	static int cof[K + 1][K + 1], tmp[K + 1][K + 1];
	void add(int &a, ll b) { a = (a + b) % P; }
	int reduce(int &a, int b) {
    	int res = a / b;
    	a %= b; if (a < 0) a += b, --res;
    	return res;
	}

	void calc(int x, bool o) {
		rep(i, 0, k) memcpy(tmp[i]+1, cof[i]+1, 4 * (k - i));
        for (int i = 1, u = x; i <= k; ++i, u = mul(u, x))
            rep(s, i, k+1) {
                int v = mul(C[s][i], u);
                rep(r, 0, k-s+1) add(cof[r + o * i][s - i], (ll)v * tmp[r][s]);
            }
	}
	
	void run() {
		freopen("a.in", "r", stdin);
    	ios::sync_with_stdio(0);
    	cin.tie(0);
    	cin >> T;
    	inv[1] = 1; rep(i, 2, K+2) inv[i] = mul(P - P / i, inv[P % i]);
    	C[0][0] = 1;
    	rep(i, 1, K+2){
        	C[i][0] = 1;
        	rep(j, 1, i+1) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
    	}
    	rep(i, 0, K+1) {
        	int sum = 0;
        	rep(j, 0, i) add(sum, mul(C[i + 1][j], B[j]));
        	B[i] = (1 + (ll)(P - sum) * inv[i + 1]) % P;
    	}
    	rep(cas, 0, T) {
        	int n, a, b, c, k1, k2, n1, a1, b1, c1;
        	cin >> n1 >> a1 >> b1 >> c1;// >> k1 >> k2;
			for (int tim = 0; tim < 3; tim++) {
				n = n1, b = b1, a = a1, c = c1;
        		if (tim == 0) k1 = 0, k2 = 1;
				if (tim == 1) k1 = 0, k2 = 2;
				if (tim == 2) k1 = 1, k2 = 1;
				k = k1 + k2;
				int res = 0, sign = 1;
        		if (k1 == 0) { res = 1; rep(i, 0, k2) res = mul(res, b / c); }
        		rep(i, 0, k) memset(cof[i]+1, 0, 4 * (k - i));
        		cof[k1][k2] = 1;
        		while (1) {
            		int cur = 0;
            		int x = reduce(a, c), y = (reduce(b, c) + P) % P;
            		calc(x, 1); calc(y, 0);
            		int l = ((ll)a * n + b) / c;
            		rep(r, 0, k+1) { //<=k
                		int sum = 0;
                		for (int i = 1, u = n; i <= r + 1; ++i, u = mul(u, n))
                    		add(sum, (ll)C[r + 1][i] * B[r + 1 - i] % P * u);
                		sum = mul(sum, inv[r + 1]);
               			for (int s = 0, u = sum; s <= k - r; ++s, u = mul(u, l)) add(cur, mul(u, cof[r][s]));
                		cof[r][0] = 0;
            		}
            		add(res, mul(sign, cur));//res = (res + (ll)sign * cur) % mod;
            		if (!a) break;
            		for (int i = 0; i < k; ++i) memset(tmp[i], 0, 4 * (k - i));
            		for (int s = 1; s <= k; ++s)
                		for (int i = 1; i <= s; ++i) {
                    		int u = (ll)C[s][i] * (i % 2 ? 1 : P - 1) % P;
                    		for (int r = 0; r <= k - s; ++r) add(tmp[r][s - i], (ll)u * cof[r][s]);
                		}
            		for (int i = 0; i < k; ++i) memset(cof[i] + 1, 0, 4 * (k - i));
            		for (int r = 0; r < k; ++r)
                		for (int i = 0; i <= r; ++i) {
                    		int u = (ll)C[r + 1][i] * B[i] % P * inv[r + 1] % P;
                    		for (int s = 0; s < k - r; ++s) add(cof[s][r + 1 - i], (ll)u * tmp[r][s]);
                		}
            		n = l;
            		swap(a, c);
            		b = -b - 1;
            		sign = P - sign;
        		}
        		cout << res << " \n"[tim == 2];
			}
    	}
	}
}  // namespace _lo
int main() { _lo::run(); }
