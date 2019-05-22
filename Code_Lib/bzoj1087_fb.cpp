//状压需要先预处理两层之间的转移 
//感觉可以轮廓线，但是影响有一列和上下都有关，不太好写 
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

const int N = 10;
int n;
vector<pii> g[1 << N];
ll f[15][1 << N][N * N];
int a[2][15], k, S;

int dx[] = {1, 1, 1, -1, -1, -1, 0, 0};
int dy[] = {-1, 0, 1, -1, 0, 1, -1, 1};

bool check(int x, int y) {
	rep(i, 0, n) if (pw(i) & x) a[0][i] = 1;else a[0][i]= 0;
	rep(i, 0, n) if (pw(i) & y) a[1][i] = 1;else a[1][i]= 0;
	rep(i, 0, 2) rep(j, 0, n) if (a[i][j]){
		rep(t, 0, 8) {
			x = i + dx[t];
			y = j + dy[t];
			if (x >= 0 && x <= 1 && y >= 0 && y < n) {
				if (a[x][y]) return 0;
			}
		} 
	}
	return 1;
}

int get(int x) {
	int cnt = 0;
	rep(i, 0, n) if (pw(i) & x) cnt++;
	return cnt;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	S = pw(n);
	rep(i, 0, S)
		rep(j, 0, S) 	
			if (check(i, j)) g[i].pb(mp(j, get(j)));
	f[0][0][0] = 1;
	rep(i, 0, n+1) {
		rep(j, 0, S) 
			rep(l, 0, k+1) if (f[i][j][l])
				rep(t, 0, sz(g[j])) {
					pii v = g[j][t];
					if (l + v.se <= k) f[i+1][v.fi][l + v.se] += f[i][j][l];
				}
	}
	cout << f[n+1][0][k];
	return 0;
}


