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

bool cmp(pii a, pii b) { return 1.0 * a.se / a.fi > 1.0 * b.se / b.fi;}

const int  N = 3e5 + 8;
ll dp[N], n, m, s;
pii a[N];

int main() {
	//freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) cin >> a[i].fi >> a[i].se;
	sort(a + 1, a + n + 1, cmp);
	rep(i, 1, n+1) {
		s = min(s + a[i].fi, m); 
		per(j, max(1ll * a[i].fi, s - 4), s + 1) dp[j] = max(dp[j], dp[j - a[i].fi] + a[i].se);
	} 
	ll ans = *max_element(dp, dp + m + 1);
	cout << ans << endl;
	return 0;
}

