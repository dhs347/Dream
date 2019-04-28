// 维护区间内出现过的球可以用所有右端点在l右边的球^所有左端点在r左边的球^所有球
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

inline int upd(int a, int b, int P) {
  //if((a += b) >= P) a -= P;
  //return a < 0 ? a + P : a;
	return a ^ b;
}

const int N = 2e5 + 7;
inline int mul(int a, int b, int P) { return 1ll * a * b % P; }
struct DHash {
  static const int P = 1e9 + 7, Q = 1e9 + 9;
  int a, b;
  DHash() { a = b = 0; }
  DHash(int a, int b) : a(a), b(b) {}
  inline DHash operator + (const DHash &c) const { return DHash(upd(a, c.a, P), upd(b, c.b, Q)); }
  inline DHash operator - (const DHash &c) const { return DHash(upd(a, -c.a, P), upd(b, -c.b, Q)); }
  inline DHash operator * (const int c) const { return DHash(mul(a, c, P), mul(b, c + 1, Q)); }
  inline bool operator == (const DHash &c) const { return a == c.a && b == c.b; }
  inline bool operator < (const DHash &c) const { if (a != c.a) return a < c.a; return b < c.b;}
} now, a[N], ALL, pre[N], suf[N];

int n, m, l, r, t;
ll ans;
map<DHash, pair<int, ll> > M;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	now = DHash(2, 3);
	ALL = DHash(0, 0);
	rep(i, 1, n+1) {
		cin >> l >> r;
		now = now * 2;
		ALL = ALL + now;
		a[l] = a[l] + now;
		a[r+1] = a[r+1] + now;
		pre[l] = pre[l] + now;
		suf[r] = suf[r] + now;
	}
	now = DHash(0, 0);
	rep(i, 1, m+1) a[i] = a[i] + a[i-1], pre[i] = pre[i] + pre[i-1];
	per(i, 1, m+1) suf[i] = suf[i] + suf[i + 1];
	rep(i, 1, m+2) if (i <= m && now == a[i]) {
		t++;
	}else {
		ans += 1ll * t * (t + 1) / 2 * (t + 1);
		ans -= 1ll * t * (t + 1) * (2 * t + 1) / 6;
		t = 0;
	}
	rep(i, 1, m+1) a[i] = a[i] + a[i-1];
	M[now + suf[1]] = mp(1, 0);
	ll tmp = 0;
	rep(i, 1, m+1) {
		now = a[i] + pre[i] + ALL;
		if (M.count(now)) {
			tmp += 1ll * M[now].fi * i - M[now].se; 
		}
		M[a[i] + suf[i+1]].fi++;
		M[a[i] + suf[i+1]].se += i;
	}
	cout << tmp - ans << endl;
	return 0; 
}


