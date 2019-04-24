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

namespace GaussInt{
	static const int N = ::N, P = 1e9 + 7;
	int x[N]; //增广矩阵和解集
	bool free_x[N]; //标记是否是不确定的变元
	int add(int a, int b) {if ((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
	int mul(int a, int b) {return 1ll * a * b % P;}
	int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
	int Gauss(int equ, int var){
		int k, col, p;
		fill_n(free_x, var, 1);
		fill_n(x, var, 0);
		for(k = col = 0; k < equ && col < var; ++k, ++col){
			p = k; rep(i, k+1, equ) if (a[i][col]) {p = i; break;}
			if (p != k) rep(j, k, var+1) swap(a[p][j], a[k][j]);
			if(!a[k][col]) {k--; continue;}
			int inv = kpow(a[k][col], P - 2);
			rep(i, col, var+1) a[k][i] = mul(a[k][i], inv);
			rep(i, k+1, equ){
				if(!a[i][col]) continue;
				int t = a[i][col];
				rep(j, col, var+1) a[i][j] = add(a[i][j], -mul(a[k][j], t));
			}
		}
		rep(i, k, equ) if (a[i][var]) return -1;//无解
		if(k < var){
			per(i, 0, k-1) {
				int num = 0;
				rep(j, 0, var) if (a[i][j] && free_x[j]) num++, p = j;
				if(num > 1) continue;
				int t = a[i][var];
				rep(j, 0, var) if (j != p && a[i][j]) t = add(t, -mul(a[i][j], x[j]));
				free_x[p] = 0;
				x[p] = t;
			}
			return var - k;//自由变元个数
		}
		per(i, 0, var) {
			int t = a[i][var];
			rep(j, i+1, var) if (a[i][j]) t = add(t, -mul(a[i][j], x[j]));
			x[i] = t;
		}
		return 0;
	}
}



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
		int t = GaussInt :: Gauss(n+1, n+1);
		if (t == -1) cout << t << endl;
		else cout << GaussInt :: x[n - p] << endl;
	} 
	return 0;
}


