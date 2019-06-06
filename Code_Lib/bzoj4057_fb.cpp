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

const int N = 20;
int T, n, a[N][N], S;
bool f[1 << N];
int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 0, n) rep(j, 0, n) cin >> a[i][j];
		S = pw(n) - 1;
		rep(i, 0, S+1) f[i] = 0;
		f[S] = 1;
		per(i, 1, S+1) if (f[i]) {
			for (int x = i, t = lb(x); x; x -= t, t = lb(x)) {
				int sum = 0, p = __builtin_ctz(t);
				for (int y = i, tt = lb(x); y; y -= tt, tt = lb(y)) sum -= a[p][__builtin_ctz(tt)]; 
				if (sum < 0) f[i ^ t] = 1;
			}
		}
		vi ans;
		rep(i, 0, n) if (f[pw(i)]) ans.pb(i); 
		if (sz(ans) == 0) cout << 0 << endl;
		else rep(i, 0, sz(ans)) cout << ans[i] + 1 << (i != sz(ans) - 1 ? " " : endl);
	}
	return 0;
}


