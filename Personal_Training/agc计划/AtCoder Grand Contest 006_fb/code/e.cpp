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
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7;
int n, t, d[10], now, a[3][N], b[10], w[N];
vi c[10];

void upd(int p) {
	for (; p <= n; p += lb(p)) w[p] ^= 1;
}

int qry(int p) {
	int r = 0;
	for (; p; p -= lb(p)) r ^= w[p];
	return r;
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n; 
	rep(j, 0, 3) rep(i, 1, n+1) cin >> a[j][i];
	rep(i, 1, n+1) {
		rep(j, 0, 3) b[j] = a[j][i];
		sort(b, b+3);
		if (a[1][i] != b[1] || b[2] - b[0] != 2 || b[0] % 3 != 1 || ((i & 1) != ((b[2] / 3) & 1))) {
			cout << "No";
			return 0;
		}
		c[i & 1].pb(b[2] / 3);
		d[i & 1] ^= a[0][i] > a[1][i];
	}
	rep(j, 0, 2) {
		rep(i, 0, n+1) w[i] = 0;
		per(i, 0, sz(c[j])) {
			//rep(k, i+1, sz(c[j])) if (c[j][i] > c[j][k]) d[j ^ 1] ^= 1; 
			d[j ^ 1] ^= qry(c[j][i]);
			upd(c[j][i]);
		}
	}
	if (d[0] == 0 && d[1] == 0) {
		cout << "Yes";
	}else cout << "No";
	return 0;
}


