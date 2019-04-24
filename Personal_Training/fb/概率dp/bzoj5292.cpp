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

const int N = 1510;
int a[N][N], T, p, m, k, n, inv[N], len, p1, p2, t[N];

namespace Gauss{
	static const int N = :: N;
	int X[N];
	int solve(int n, int m){//n=equ, m=var ͬ Gaussxor
		int i = 0, x = 0;
		for(; i < n && x < m; i++, x++){
			int r = i;
			while(r < n && !a[r][x]) r++;
			if(r >= n){
				return -1;
				i--;
				continue;
			}
			if (r != i) return -1;
			//if(r != i) rep(j, 0, m+1) swap(a[r][j], a[i][j]);
			int inv = kpow(a[i][x], P-2);
			for(int k = m; k >= x; k--) a[i][k] = mul(a[i][k], inv); //a[i][k] * inv % P;
			rep(j, i+1, n)
				if(a[j][x]) {
					for(int k = m; k >= x; k--)
						a[j][k] = add(a[j][k], -mul(a[i][k], a[j][x]));
					break;
				}else break;
		}
		rep(k, i, n) if (a[k][m]) return -1;
		rep(k, i, m+1) X[k] = 0;
		per(k, 0, i) {
			X[k] = a[k][m];
			rep(l, k+1, m) X[k] = add(X[k], -mul(X[l], a[k][l]));
		}
		return m - i;
	}
	void out(int n, int m){
		rep(i, 0, n){
			rep(j, 0, m+1)cout<<a[i][j]<<' ';
			cout<<endl;
		}
		rep(i, 0, m) de(X[i]);
	}
};



int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	inv[1] = 1;
	rep(i, 2, 1500+1) inv[i] = mul((P - P / i), inv[P % i]); 
	rep(cas, 0, T) {
		cin >> n >> p >> m >> k;
		len = min(n, k);
		p1 = kpow(m + 1, P - 2); p2 = mul(p1, m); 
		int INV = kpow(m, P - 2);
		t[0] = kpow(p2, k);
		rep(i, 1, len+1) {
			t[i] = mul(t[i-1], mul(INV, mul(k - i + 1, inv[i])));
			if (m == 0 && i == k) t[i] = 1;
		}	
		rep(i, 0, n+2) fill_n(a[i], n+2, 0);
		a[n][n] = 1; a[n][n + 1] = 0;
		rep(i, 1, n+1) {
			a[n - i][n - i] = 1;
			a[n - i][n + 1] = 1;
			rep(j, 0, min(k, i)+1) {
				if (i != n) {
					a[n - i][n - (i + 1 - j)] = add(a[n - i][n - (i + 1 - j)], -mul(t[j], p1));
					a[n - i][n - (i - j)] = add(a[n - i][n - (i - j)], -mul(t[j], p2));
				}else {
					a[n - i][n - (i - j)] = add(a[n - i][n - (i - j)], -t[j]);
				}
			}
		}
		int t = Gauss :: solve(n+1, n+1);
		if (t == -1) cout << t << endl;
		else cout << Gauss :: X[n - p] << endl;
	} 
	return 0;
}


