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

const int N = 205;
int n, m, id[N][2], u, v, w;
vector<pii> g[N];
db ans;

namespace GaussDB{
	static const int N=210;
	double mat[N][N];//增广矩阵
	double x[N];//解集
	bool free_x[N];//标记是否是不确定的变元
	const double eps = 1e-10;
	int Gauss(int equ, int var){
		int k;
		int max_r, col;
		int free_index, free_num;
		memset(free_x, 1, sizeof(free_x));
		memset(x, 0, sizeof(x));
		for(k=col=0; k<equ&&col<var; ++k, ++col){
			max_r=k;
			rep(i, k+1, equ)
				if(fabs(mat[i][col])-mat[max_r][col]>eps) max_r=i;
			if(max_r!=k)
				rep(j, k, var+1)swap(mat[max_r][j], mat[k][j]);
			if(fabs(mat[k][col]<eps)){--k;continue;}
			rep(i, k+1, equ){
				if(fabs(mat[i][col])<=eps) continue;
				double tmp=mat[i][col]/mat[k][col];
				rep(j, col, var+1)
					mat[i][j]-=mat[k][j]*tmp;
			}

		}
		rep(i, k, equ)
			if(fabs(mat[i][var]>eps)) return 0;//无解
		if(k<var){
			for(int i=k-1; i>=0; --i){
				free_num=0;
				rep(j, 0, var){
					if(fabs(mat[i][j])>eps&&free_x[j]){
						free_num+=1;
						free_index=j;
					}
				}
				if(free_num>1) continue;
				double tmp=mat[i][var];
				rep(j, 0, var){
					if(j!=free_index&&fabs(mat[i][j])>eps)
						tmp-=mat[i][j]*x[j];
				}
				free_x[free_index]=0;
				x[free_index]=tmp/mat[i][free_index];
			}
			return var-k;//自由变元个数
		}
		for(int i=var-1; i>=0; --i){
			double tmp=mat[i][var];
			rep(j, i+1, var){
				if(fabs(mat[i][j])>eps)
					tmp-=x[j]*mat[i][j];
			}
			x[i]=tmp/mat[i][i];
		}
		return 1;
	}
	void solve(int n) {
		rep(len, 0, 31) {
			rep(i, 0, 2*n+1) rep(j, 0, 2*n+1) mat[i][j] = 0;
			mat[id[1][0]][2 * n] = 1;
			rep(i, 1, n+1) {
				rep(j, 0, 2) {
					mat[id[i][j]][id[i][j]] += 1;
					if (i != n) rep(k, 0, sz(g[i])) {
						bool o = g[i][k].se & pw(len);
						mat[id[g[i][k].fi][o ^ j]][id[i][j]] -= 1.0 / sz(g[i]);
					}
				}
			} 
			Gauss(2 * n, 2 * n);
			ans += x[id[n][1]] * pw(len);
		}
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
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		if (u != v) g[v].pb(mp(u, w));
	}
	rep(i, 1, n+1) id[i][0] = i - 1, id[i][1] = id[i][0] + n;
	GaussDB :: solve(n);
	cout << ans << endl;
	return 0;
}

