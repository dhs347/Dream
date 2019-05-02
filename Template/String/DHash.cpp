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
#define all(a) a.begin(), a.end()
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

const int N = 1e5 + 7;

inline int upd(int a, int b, int P) {
  if((a += b) >= P) a -= P;
  return a < 0 ? a + P : a;
}

inline int mul(int a, int b, int P) {return 1ll * a * b % P; }

struct Int{
  static const int P = 1e9 + 7, Q = 1e9 + 9;
  int a, b;
  Int(int a = 0, int b = 0) : a(a), b(b) {}
  inline Int operator + (const Int &c) const { return Int(upd(a, c.a, P), upd(b, c.b, Q)); }
  inline Int operator - (const Int &c) const { return Int(upd(a, -c.a, P), upd(b, -c.b, Q)); }
  inline Int operator * (const Int &c) const { return Int(mul(a, c.a, P), mul(b, c.b, Q)); }
} _0 = Int(0, 0), _1 = Int(1, 1), B[N];

void init(int n){
	B[0] = _0; B[1] = Int(233, 233);
	rep(i, 1, n+1) B[i] = B[i-1] * B[1];
}

struct Str{
	Int a; int len;
	Str(Int a = _0, int len = 0) : a(a), len(len) {}
	Str(int x) {a = Int(x, x); len = 1;}
	inline Str operator + (const Str &c) const { return Str(a * B[c.len] + c.a, len + c.len); }
	inline Str operator - (const Str &c) const { return Str(a - c.a * B[len - c.len], len - c.len); }
} ha[N];

void init(Str *ha, string &s) {
	ha[0] = Str(s[0] + 1);
	rep(i, 1, sz(s)) ha[i] = ha[i-1] + Str(s[i] + 1);
}

Str sub(Str *ha, int l, int r) {
	if (l > r) return Str();
	if (l == 0) return ha[r];
	return ha[r] - ha[l-1]; 
}

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	Str a;
	return 0;
}





