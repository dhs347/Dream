// 分步优化转移 
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

int n, m, d[105], a[105][20];
int f[1 << 16], g[1 << 16], S;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) {
		cin >> d[i];
		rep(j, 0, m) cin >> a[i][j];
	}
	S = pw(m) - 1;
	memset(f, 0x3f, sizeof(f));
	f[S] = 0;
	rep(i, 1, n+1) {
		rep(j, 0, S+1) g[j] = f[j] + d[i];
		per(j, 0, S+1) 
			for (int x = j, t = lb(x); x; x -= t, t = lb(x)) {
				int p = __builtin_ctz(t);
				g[j ^ t] = min(g[j ^ t], g[j] + a[i][p]);
			}
		rep(j, 0, S+1) f[j] = min(f[j], g[j]); 
	}
	cout << f[0];
	return 0;
}


