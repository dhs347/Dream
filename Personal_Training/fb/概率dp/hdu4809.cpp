//偏树形dp，和概率关系比较小
//树上每个点可分给三个人，每个人消耗他有的奇数联通块数减偶数联通块数的代价，求代价和期望 
//记录i的联通块奇偶性和已有的差值，与儿子转移一下 
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
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 305;
const int d = 301; 
int dp[N][N * 2][3], tmp[N * 2][3], siz[N], n, u, v, ans;
vi g[N];
int w[] = {-1, 1, 0};

void dfs(int u, int fa) {
	siz[u] = 1;
	dp[u][d][1] = 1;
	dp[u][d][2] = 2;
	for (auto v : g[u]) if (v != fa) {
		dfs(v, u);
		rep(i, -siz[u] - siz[v] + d, siz[u] + siz[v] + d + 1) 
			rep(j, 0, 3) tmp[i][j] = 0;
		rep(i, -siz[u] + d, siz[u] + d + 1) 
			rep(j, -siz[v] + d, siz[v] + d + 1) 
				rep(k, 0, 3)
					rep(l, 0, 3) {
						if (k <= 1 && l <= 1) {
							int &t = tmp[i + j - d][k ^ l];
							t = add(t, mul(dp[u][i][k], dp[v][j][l]));
						}
						if (k > 1) {
							int &t = tmp[i + j + w[l] - d][k];
							t = add(t, mul(dp[u][i][k], dp[v][j][l]));
						}else if (l > 1) {
							int &t = tmp[i + j - d][k];
							t = add(t, mul(dp[u][i][k], dp[v][j][l]));
						}
					}
		siz[u] += siz[v];
		rep(i, -siz[u] + d, siz[u] + d + 1) 
			rep(j, 0, 3) dp[u][i][j] = tmp[i][j];
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while(cin >> n) {
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, n) {
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		rep(i, 1, n+1) rep(j, -n + d, n + d + 1) rep(k, 0, 3) dp[i][j][k] = 0;
		dfs(1, 0);
		ans = 0;
		rep(i, d, n + d + 1) 
			rep(j, 0, 3) {
				ans = add(ans, mul(max(0, i - d + w[j]), dp[1][i][j]));
			}
		cout << mul(ans, 3) << endl;
	} 
	return 0;
}

