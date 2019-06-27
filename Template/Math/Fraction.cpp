template<class T>
struct Fra{
	T a, b;
	Fra() : a(0), b(1) {}
	Fra(string s) {
		stringstream ss(s); char c;
		ss >> a >> c >> b;
		*this = Fra(a, b);
	}
	Fra(T c) : a(c), b(1) {}
	Fra(T _a, T _b) {
		T d = __gcd(_a, _b);
		a = _a / d, b = _b / d;
		if(b < 0) a = -a, b = -b;
	}
	Fra operator + (const Fra &c) const { return Fra(a * c.b + b * c.a, b * c.b); }
	Fra operator - (const Fra &c) const { return Fra(a * c.b - b * c.a, b * c.b); }
	Fra operator * (const Fra &c) const { return Fra(a * c.a, b * c.b); }
	Fra operator / (const Fra &c) const { return Fra(a * c.b, b * c.a); }
	Fra operator * (const T &c) const { return Fra(a * c, b); }
	Fra operator / (const T &c) const { return Fra(a, b * c); }
	bool operator == (const Fra &c) const { return a == c.a && b == c.b; }
	bool operator != (const Fra &c) const { return !(*this == c); }
	void print() { cout << a << "/" << b; }
};
typedef Fra<ll> fll;
