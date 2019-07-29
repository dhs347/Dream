const int P = 1e9 + 7;
inline int upd(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
inline int mul(int a, int b) {return 1ll * a * b % P; }

struct Int{
	int a, b;
	Int(int a = 0, int b = 0) : a(a), b(b) {}
	inline Int operator + (const Int &c) const { return Int(upd(a, c.a), upd(b, c.b)); }
	inline Int operator - (const Int &c) const { return Int(upd(a, -c.a), upd(b, -c.b)); }
	inline Int operator * (const Int &c) const { return Int(mul(a, c.a), mul(b, c.b)); }
	inline bool operator == (const Int &c) const {return a == c.a && b == c.b;}
} _0 = Int(), _1 = Int(1, 1), B[N];

void init(int n){
	B[0] = _1; B[1] = Int(233, 241);
	rep(i, 2, n+1) B[i] = B[i-1] * B[1];
}

struct Str{
	Int a; int len;
	Str(Int a = _0, int len = 0) : a(a), len(len) {}
	Str(int x) {a = Int(x, x); len = 1;}
	inline Str operator + (const Str &c) const { return Str(a * B[c.len] + c.a, len + c.len); }
	inline Str operator - (const Str &c) const { return Str(a - c.a * B[len - c.len], len - c.len); } // 减去一个前缀
	inline bool operator == (const Str &c) const { return a == c.a && len == c.len;}
} ha[N], hb[N];

void init(vi &s, Str *ha) {
	rep(i, 0, sz(s)) ha[i] = i > 0 ? ha[i-1] + Str(s[i] + 1) : Str(s[0] + 1);
}

Str sub(Str *ha, int l, int r) {
	if (l > r) return Str();
	return l > 0 ? ha[r] - ha[l-1] : ha[r]; 
}
