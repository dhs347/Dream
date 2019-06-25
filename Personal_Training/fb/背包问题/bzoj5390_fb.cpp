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

const int N = 1e5 + 67;
ll w[N], v[N], l[N], f[N][105], d[N], n, m;

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, m+1) cin >> d[i];
	rep(i, 1, n+1) cin >> w[i] >> v[i] >> l[i];
	memset(f, -10, sizeof(f));
	rep(i, 1, n+1) f[0][i] = 0;
	ll pre = 0;
	rep(i, 0, m+1) {
		rep(j, 1, n+1) if (i > w[j]) f[i][j] = max(f[i][j], f[i - w[j]][j] + v[j]);
		ll t = *max_element(f[i] + 1, f[i] + n + 1);
		pre = max(pre, t);
		rep(j, 1, n+1) if (i + l[j] * w[j] <= m) f[i + l[j] * w[j]][j] = max(f[i + l[j] * w[j]][j], v[j] * l[j] + t - d[i]);
		if (i > 0) cout << pre << " \n"[i == m];  
	} 
	return 0; 
}


