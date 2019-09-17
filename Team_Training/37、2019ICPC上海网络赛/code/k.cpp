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

vector<vi> ans;

int A, B, C, T, m;

vector<pii> get(int n) {
	vector<pii> res, res2;
	
	m = sqrt(n);
	rep(i, 1, m+1) if (n % i == 0){
		int t = i * 2;
		for (int j = 3; j * j < t; j += 2) if (2ll * j * j > t) {
			int k = sqrt(t - j * j);
			if (k * k + j * j == t && (k & 1) && __gcd(k, j) == 1) {
				int a = j * k, b = (j * j - k * k) / 2;
				res2.pb(mp(a * (n / i), b * (n / i)));
				res2.pb(mp(b * (n / i), a * (n / i)));
			} 
		}
		t = n / i * 2;
		if (i * i != n) {
			for (int j = 3; j * j < t; j += 2) if (2ll * j * j > t) {
				int k = sqrt(t - j * j);
				if (k * k + j * j == t && (k & 1) && __gcd(k, j) == 1) {
					int a = j * k, b = (j * j - k * k) / 2;
					res2.pb(mp(a * i, b * i));
					res2.pb(mp(b * i, a * i));
				} 
			}
		}
	}
	res = res2;
	for (auto u : res2) res.pb(mp(-u.fi, u.se));
	for (auto u : res2) res.pb(mp(u.fi, -u.se));
	for (auto u : res2) res.pb(mp(-u.fi, -u.se));
	res.pb(mp(0, n));
	res.pb(mp(n, 0));
	res.pb(mp(0, -n));
	res.pb(mp(-n, 0));
	return res;
}

bool check(pii a, pii b, int c) {
	if (1ll * (a.fi - b.fi) * (a.fi - b.fi) + 1ll * (a.se - b.se) * (a.se - b.se) == 1ll * c * c) return 1;
	return 0;
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> A >> B >> C;
		ans.clear();
		vector<pii> t1 = get(A), t2 = get(B);
		for (auto u : t1) for (auto v : t2) if (check(u, v, C)) {
			vi t; t.pb(u.fi); t.pb(u.se); t.pb(v.fi); t.pb(v.se);
			ans.pb(t);
		}
		sort(all(ans));
		cout << sz(ans) << endl;
		for (auto u : ans) {
			rep(i, 0, sz(u)) cout << u[i] << " \n"[i == sz(u) - 1];
		}
	}
	return 0;
}


