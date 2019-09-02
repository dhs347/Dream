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
int P;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7;
int T, n, k;
ll t1[N], t2[N], ans;

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> k >> P;
		ans = 0;
		//jc[0] = 1; rep(i, 1, n+1) jc[i] = jc[i-1] * i % P;
		t1[0] = 1; rep(i, 1, n+1) t1[i] = t1[i-1] * (min(i + k, n) - (i - 1)) % P;
		t2[n+1] = 1; per(i, 1, n+1) t2[i] = t2[i+1] * (min(i + k, n) - (i - 1)) % P;
		rep(i, 1, n+1)
			rep(j, i+1, n+1) {
				if (j - 1 + k < n) {
					ans += t1[j-1] * t2[j+1] % P, ans %= P;  
					if (j - i > 1) ans += t1[i] * t2[j+1] % P, ans %= P;
				}
			}
		ans += t1[n];
		ans %= P;
		cout << "Case #" << cas + 1 << ": " << ans << endl;
	}
	return 0;
}


