//层之间的有序性要考虑清楚，最好写成分层的形式 
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

const int N = 15;
int n, m, a[N][N], b[N][N], c[N], S, w1[1 << 10][N], w2[1 << 10], f[100][1 << 10], ans;

int cal1(int x, int m) {
	int res = 0;
	rep(i, 0, n) if (pw(i) & x) res += a[i][m];
	return res;
}

int cal2(int x) {
	int res = 0;
	rep(i, 0, n) if (pw(i) & x) 
		rep(j, i+1, n) if (pw(j) & x) res += b[i][j];
	return res;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n >> m) {
		if  (n == 0 && m == 0) break;
		rep(i, 1, m+1) cin >> c[i];
		rep(i, 0, n) rep(j, 1, m+1) cin >> a[i][j];
		rep(i, 0, n) rep(j, 0, n) cin >> b[i][j];
		S = pw(n) - 1;
		rep(i, 0, S+1) {
			rep(j, 1, m+1) w1[i][j] = cal1(i, j);
			w2[i] = cal2(i);
		}
		memset(f, -0x3f, sizeof(f));
		rep(i, 0, S+1) f[0][i] = 0;
		rep(t, 1, m+1) {
			rep(i, 0, S+1) {
				for (int x = i; x >= 0; x = (x - 1) & i) {
					f[t][x] = max(f[t][x], f[t-1][i] + w1[x][t] + w2[x] - __builtin_popcount(x) * c[t]);
					if (x == 0) break;
				}	
			}
		}
		ans = *max_element(f[m], f[m]+S+1);
		if (ans <= 0) cout << "STAY HOME" << endl;else cout << ans << endl;
	}
	return 0;
}


