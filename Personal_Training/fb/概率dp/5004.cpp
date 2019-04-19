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

const int N = 310;
int T, n, nn, vis[N], a[N], x, cnt, m;
db c[N][N], tmp[N], f[N];
vi cir;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(9);
	cin >> T;
	rep(i, 0, 305) {
		c[i][0] = 1;
		rep(j, 1, i+1) {
			c[i][j] = c[i-1][j-1] + c[i-1][j];
		}
	}
	rep(cas, 0, T) {
		cin >> n >> m;
		cir.clear();
		rep(i, 1, n+1) cin >> a[i], vis[i] = 0;
		rep(i, 1, n+1) if (!vis[i]){
			x = i; cnt = 0;
			while (!vis[x]) {
				vis[x] = 1;
				cnt++; x = a[x];
			}
			cir.pb(cnt);
		}
		rep(i, 0, n+1) f[i] = 0, tmp[i] = 0;
		f[0] = 1;
		rep(i, 0, sz(cir)) {
			rep(j, 1, cir[i]+1) 
				rep(k, j, n+1) tmp[k] += f[k - j] * c[cir[i]][j]; 	
			rep(k, 0, n+1) f[k] = tmp[k], tmp[k] = 0;
		}
		cout << f[m] / c[n][m] << endl;  
	} 
	return 0;
}

