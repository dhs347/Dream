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
typedef pair<int, ll> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

bool check(pii a, pii b, pii c) {
	return 1ll * (b.se - a.se) * (c.fi - b.fi) < 1ll * (c.se - b.se) * (b.fi - a.fi);
}

bool check2(pii a, pii b, int k) {
	return 1ll * k * (b.fi - a.fi) > (b.se - a.se);
}

const int N = 1e5 + 7;
int T, n, m, k, a[N];
ll anss, s1[N], s[N], tmp[N], ans[N];
pii h[N];

void print(pii x) {
	dd(x.fi); de(x.se);
}
int main() {
//	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> k >> m; vi V;
		rep(i, 1, n+1) {
			cin >> a[i];
			V.pb(a[i] * (n - i + 1));
		}
		anss = 0;
		sort(all(V));
		per(i, 0, sz(V)) {
			if (!m) break;
			m--; anss += V[i];
		}
		reverse(a + 1, a + n + 1);
		rep(i, 1, n+1) s1[i] = s1[i-1] + i * a[i], s[i] = s[i-1] + a[i];
		tmp[0] = 0;
		rep(i, 1, n+1) tmp[i] = pw(40);
		rep(j, 1, k+2) {
			int l = 0, r = 0; 
			rep(i, 1, n+1) {
				ll y = tmp[i-1] - s1[i-1] + s[i-1] * (i - 1);
				pii t = mp(i-1, y);
				while (r - l >= 2 && !check(h[r-2], h[r-1], t)) r--;
				h[r++] = t;
				while (r - l > 1 && check2(h[l], h[l+1], s[i])) l++;
				ans[i] = h[l].se - s[i] * h[l].fi + s1[i];  
			}
			rep(i, 0, n+1) tmp[i] = ans[i];
		}
		cout << anss - ans[n] << endl; 
	} 
	return 0;
}


