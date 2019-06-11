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

const int N = 2e3 + 10;
int n, f[N][N];
pii a[N];
int main() {
	//freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i].fi >> a[i].se;
	sort(a+1, a+n+1);
	reverse(a+1, a+n+1);
	memset(f[0], -0x3f, sizeof(f));
	f[0][0] = f[0][1] = 0;
	rep(i, 1, n+1) {
		rep(j, 0, n+1) f[i][j] = max(f[i-1][j], f[i-1][max(j + 1 - a[i].fi, 1)] + a[i].se);  
	}
	int ans = *max_element(f[n], f[n] + n + 1);
	cout << ans << endl;
	return 0;
}


