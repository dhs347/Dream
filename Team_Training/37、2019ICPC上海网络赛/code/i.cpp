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
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

int T;
ll n, a, b, l, ans;
__int128 an;

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> a >> b;
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}
		an = (__int128)pw(62) * pw(62);
		rep(i, 1, 64) {
			l = powl(n, 1.0 / i);
			ll t = n; ans = pw(62);
			rep(j, 0, i+1) {
				ll tt = t;
				rep(k, 0, i - j) tt = (tt - 1) / (l+1) + 1;
				if (tt <= 1) ans = min(ans, j * (l - 1) + (i - j) * l);  
				t = (t - 1) / l + 1;
			}
			an = min(an, (__int128)a * i + (__int128)ans * b);
		}
		vi tmp;
		while (an) {
			tmp.pb(an % 10);
			an /= 10;
		}
		if (!sz(tmp)) cout << 0 << endl;
		else {per(i, 0, sz(tmp)) cout << tmp[i]; cout << endl;}
	}
	return 0;
}


