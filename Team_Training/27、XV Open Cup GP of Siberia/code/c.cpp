#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e6 + 7;

int n;
ll len[N];
string s;

const int P = 1e9 + 7;

inline int upd(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
inline int mul(int a, int b) {
	return 1ll * a * b % P;
}
struct Int {
	int a, b;
	Int(int a = 0, int b = 0) : a(a), b(b) {}
	inline Int operator + (const Int &c) const {
		return Int(upd(a, c.a), upd(b, c.b));
	}
	inline Int operator - (const Int &c) const {
		return Int(upd(a, -c.a), upd(b, -c.b));
	}
	inline Int operator * (const Int &c) const {
		return Int(mul(a, c.a), mul(b, c.b));
	}
	inline bool operator == (const Int &c) const {
		return a == c.a && b == c.b;
	}
} _0 = Int(), _1 = Int(1, 1), B[N];

void init(int n) {
	B[0] = _1, B[1] = Int(233, 241);
	rep(i, 2, n + 1) B[i] = B[i - 1] * B[1];
}

struct Str {
	Int a; int len;
	Str(Int a = _0, int len = 0) : a(a), len(len) {}
	Str(int x) {
		a = Int(x, x); len = 1;
	}
	inline Str operator + (const Str &c) const {
		return Str(a * B[c.len] + c.a, len + c.len);
	}
	inline Str operator - (const Str &c) const {
		return Str(a - c.a * B[len - c.len], len - c.len);
	}
	inline bool operator == (const Str & c) const {
		return a== c.a && len == c.len;
	}
}ha[N], hb[N];

void init(string &s, Str *ha) {
	rep(i, 0, sz(s)) ha[i] = i > 0 ? ha[i - 1] + Str(s[i] + 1) : Str(s[0] + 1);
}

Str sub(Str *ha, int l, int r) {
	if(l > r) return Str();
	return l > 0 ? ha[r] - ha[l - 1] : ha[r];
}

bool check(int k) {
	int m;
	for(int i = 1; ; ++i) {
		len[i] = len[i - 1] * k + k - 1;
		if(len[i] >= n) {
			m = i;
			break;
		}
	}
	rep(i, 2, m + 1) {
		int st = len[i - 1] + 1, ed = st + len[i - 1] - 1; ed = min(ed, n - 1);
		Str u;
		for(int j = 2; j <= k; ++j) {
			if(st > ed) break;
			if(ed - st + 1 != len[i - 1]) {
				u = sub(ha, 0, ed - st);
			} else if(j == 2) {
				u = sub(ha, 0, len[i - 1] - 1);
			}
			auto v = sub(ha, st, ed);
			if(!(u == v)) return 0;
			st += len[i - 1] + 1, ed += len[i - 1] + 1;
			ed = min(ed, n - 1);
		}
	}
	return 1;
}

void solve() {
	cin >> s;
	n = sz(s);
	init(s, ha);
	for(int k = 2; ; ++k) if(check(k)) {
		cout << k << endl;
		return ;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	init(N - 6);
	while(T--) {
		solve();
	}
	return 0;
}
