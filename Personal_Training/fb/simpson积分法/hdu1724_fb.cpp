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
db l, r, a, b;
const db eps = 1e-6;

namespace Simpson {
	inline db F(db x) { return sqrt((1 - x * x / a / a) * b * b); }//F(x) = ? }
	inline db simpson(db fa, db fb, db fc, db a, db c) {
		return (fa + 4 * fb + fc) * (c - a) / 6;
	}
	db asr(db a, db b, db c, db esp, db A, db fa, db fb, db fc) {
		db ab = (a + b) / 2, bc = (b + c) / 2;
		db fab = F(ab), fbc = F(bc);
		db L = simpson(fa, fab, fb, a, b), R = simpson(fb, fbc, fc, b, c);
		if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
		return asr(a, ab, b, esp / 2, L, fa, fab, fb) + asr(b, bc, c, esp / 2, R, fb, fbc, fc);
	} 
	//f(a, c)
	db asr(db a, db c, db eps) {
		db b = (a + c) / 2;
		db fa = F(a), fb = F(b), fc = F(c);
		return asr(a, b, c, eps, simpson(fa, fb, fc, a, c), fa, fb, fc);
	}
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(3);
	cin >> T;
	rep(cas, 0, T) {
		cin >> a >> b >> l >> r;
		cout << 2 * Simpson :: asr(l, r, eps) << endl;
	}
	return 0;
}


