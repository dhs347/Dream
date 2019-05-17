namespace SBT {
	typedef long double db;
	typedef int U;
	typedef pair<U, U> pii; 
	const U INF = 1e9 + 7;
	typedef __int128 T;
	typedef pair<T, T> V; // V = [double|long double|fraction]
	inline int cmp(const V &a, const V &b) {
		T x = a.fi * b.se - a.se * b.fi;
		return (x > 0) - (x < 0);
	}
	inline bool in(const V &a, const V &b, const V &c) {
		return 0 <= cmp(c, a) && cmp(c, b) < 0;
	}
	pii operator+(const pii &a, const pii &b) {
		return mp(a.fi + b.fi, a.se + b.se);
	}
	pii operator*(const pii &a, U x) {
		return mp(a.fi * x, a.se * x);
	}
	bool search(V v, U MAXB, pii &lo, pii &hi, int f) {
		V x;
		U l = 0, r = f > 0 ? (hi.se ? (MAXB - lo.se) / hi.se : INF) : 
			(lo.se ? (MAXB - hi.se) / lo.se : INF);
		while (l + 1 < r) {
			U z = (l + r) >> 1;
			x = f > 0 ? lo + hi * z : lo * z + hi;
			f * cmp(x, v) <= 0 ? l = z : r = z;
		}
		x = f > 0 ? lo + hi * r : lo * r + hi;
		r = f * cmp(x, v) <= 0 ? r : l;
		f > 0 ? lo = lo + hi * r : hi = lo * r + hi;
		return r > 0;
	}
	pii solve(V v, U MAXB) { // find ROUND_HALF_UP(a / b) = v, b <= MAXB
		V L = mp(v.fi * 10 - 5, v.se * 10);	
		V R = mp(v.fi * 10 + 5, v.se * 10);
		pii lo(0, 1), hi(1, 0);
		while (true) {
			bool ok = 0;
			//V m = mp(lo.fi + hi.fi, lo.se + hi.se);	
			//if (in(L, R, m)) return mp(m.fi, m.se);
			ok |= search(v, MAXB, lo, hi, 1);
			ok |= search(v, MAXB, lo, hi, -1);
			if (!ok) break;
		}
		db t1 = (db) lo.fi / lo.se; 
		db t2 = (db) hi.fi / hi.se;
		db t3 = (db) v.fi / v.se;
		if (t2 - t3 <= t3 - t1) return hi;else return lo;
		//if (in(L, R, lo)) return lo;
		//if (in(L, R, hi)) return hi;
		return mp(-1, -1);
	}
};