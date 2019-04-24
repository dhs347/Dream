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

const int N = 505;
int n, m, u, v;
vector<pii> g[N];
db ans, w[N * N];

namespace GaussDB{
	static const int N = 505;
	db mat[N][N], x[N]; //增广矩阵和解集
	bool free_x[N]; //标记是否是不确定的变元
	const db eps = 1e-14;
	int Gauss(int equ, int var){
		int k, col, p;
		fill_n(free_x, var, 1);
		fill_n(x, var, 0);
		for(k = col = 0; k < equ && col < var; ++k, ++col){
			p = k;
			rep(i, k+1, equ) if(fabs(mat[i][col]) > fabs(mat[p][col])) p = i;
			if (p != k) rep(j, k, var+1) swap(mat[p][j], mat[k][j]);
			if(fabs(mat[k][col]) < eps) {k--; continue;}
			rep(i, k+1, equ){
				if(fabs(mat[i][col]) < eps) continue;
				db t = mat[i][col] / mat[k][col];
				rep(j, col, var+1) mat[i][j] -= mat[k][j] * t;
			}
		}
		rep(i, k, equ) if (fabs(mat[i][var]) > eps) return -1;//无解
		if(k < var){
			per(i, 0, k-1) {
				int num = 0;
				rep(j, 0, var) if(fabs(mat[i][j]) > eps && free_x[j]) num++, p = j;
				if(num > 1) continue;
				db t = mat[i][var];
				rep(j, 0, var) if(j != p && fabs(mat[i][j]) > eps) t -= mat[i][j] * x[j];
				free_x[p] = 0;
				x[p] = t / mat[i][p];
			}
			return var - k;//自由变元个数
		}
		per(i, 0, var) {
			db t = mat[i][var];
			rep(j, i+1, var) if (fabs(mat[i][j]) > eps) t -= x[j] * mat[i][j];
			x[i] = t / mat[i][i];
		}
		return 0;
	}
	void solve(int n) {
		mat[0][n] = 1;
		rep(i, 1, n+1) {
			mat[i-1][i-1] += 1;
			if (i != n) rep(j, 0, sz(g[i])) {
				mat[g[i][j].fi-1][i-1] -= 1.0 / sz(g[i]);
			}
		} 
		Gauss(n, n);
		rep(i, 1, n) rep(j, 0, sz(g[i])) w[g[i][j].se] += x[i-1] / sz(g[i]);
		sort(w, w+m);
		rep(i, 0, m) ans += w[i] * (m - i);
	} 
}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(3);
	cin >> n >> m;
	rep(i, 0, m) {
		cin >> u >> v;
		g[u].pb(mp(v, i));
		if (u != v) g[v].pb(mp(u, i));
	}
	GaussDB :: solve(n);
	cout << ans << endl;
	return 0;
}

