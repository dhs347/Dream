// 求边双联通子图个数 
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

const int N = 1 << 10;
int n, S, e[N][N], way[N][N], a[100], t, x, y, dc[N], c[N], c2[N], c1[N], pw2[500], T, m, u, v;

//c 联通子图个数
//dc 不联通子图个数
//c1 单联通子图个数
//c2 边双联通子图个数 


void solve1() {
	S = pw(n) - 1;
	rep(i, 0, S+1) rep(j, 0, S+1) {
		e[i][j] = 0;
		rep(k, 0, n) if (pw(k) & i) e[i][j] += __builtin_popcount(a[k] & j);
	}
	rep(i, 1, S+1) {
		dc[i] = 0;
		for (int msk = (i - 1) & i; msk >= 0; msk = (msk - 1) & i) {
			if (msk & lb(i)) dc[i] = add(dc[i], mul(c[msk], pw2[e[i ^ msk][i ^ msk] / 2]));
			if (msk == 0) break;
		}
		c[i] = sub(pw2[e[i][i] / 2], dc[i]); 
	}
}

void solve2() {
	rep(j, 1, S+1) way[0][j] = 1;
	rep(i, 1, S+1) rep(j, 1, S+1) {
		if ((j & i) || lb(j) > lb(i)) continue;
		way[i][j] = 0;
		for (int msk = i; msk >= 0; msk = (msk - 1) & i) {
			if (msk & lb(i)) way[i][j] = add(way[i][j], mul(mul(way[i ^ msk][j], c[msk]), e[msk][j]));
			if (msk == 0) break;
		}
	}	
	rep(i, 1, S+1) {
		c1[i] = 0;	
		for (int msk = (i - 1) & i; msk >= 0; msk = (msk - 1) & i) {
			if (msk & lb(i)) c1[i] = add(c1[i], mul(way[i ^ msk][msk], c2[msk]));
			if (msk == 0) break;
		}
		c2[i] = sub(c[i], c1[i]);
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	pw2[0] = 1;
	rep(i, 1, 300) pw2[i] = pw2[i-1] * 2 % P;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 0, n) a[i] = (pw(n) - 1) ^ pw(i);
		rep(i, 0, m) {
			cin >> u >> v;
			u--;v--;
			a[u] ^= pw(v);
			a[v] ^= pw(u);
		}
		solve1();
		solve2();
		cout << c2[S] << endl;
	}
	return 0;
}


