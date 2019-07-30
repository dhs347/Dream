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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 998244353;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, ll b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 105;
int C[N][N], f[N][N], ans, T, c[2];
ll n, m;

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	rep(i, 0, 100) {
		C[i][0] = 1;
		rep(j, 1, i+1) C[i][j] = add(C[i-1][j], C[i-1][j-1]);
	}
	cin >> T;
	rep(i, 0, 64) rep(j, 0, 64) {
		rep(k, 0, i+1) rep(l, 0, j+1) if ((k + l * 2) % 3 == 0) f[i][j] = add(f[i][j], mul(C[i][k], C[j][l]));
	}
	rep(cas, 0, T) {
		cin >> n >> m;
		ans = 0; c[0] = c[1] = 0;
		rep(i, 0, 63) if (pw(i) & m) c[i&1]++;
		rep(i, 0, c[0]+1) rep(j, 0, c[1]+1) {
			int op = c[0] + c[1] - i - j;
			if (op & 1) ans = add(ans, -mul(mul(C[c[0]][i], C[c[1]][j]), kpow(f[i][j], n)));
			else ans = add(ans, mul(mul(C[c[0]][i], C[c[1]][j]), kpow(f[i][j], n)));
		}
		cout << ans << endl;
	} 
	return 0;
}


