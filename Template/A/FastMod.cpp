template<class T1, class T2>
struct FastD {
  	const static int wb = sizeof(T1) * 8;
  	int len; T1 m, x;
  	FastD() = default;
  	FastD(T1 n): m(n) {
    	if (n == 1) x = 1, len = 0;
    	else {
    		if (wb == 32) len = 31 - __builtin_clz(n - 1) + wb;
    		else len = 63 - __builtin_clzll(n - 1) + wb;
      		x = ((T2(1) << len) + n - 1) / n;
    	}
  	}
  	friend T1 operator / (const T1 &n, const FastD &d) { return T2(n) * d.x >> d.len; }
  	friend T1 operator % (const T1 &n, const FastD &d) { return n - n / d * d.m; }
};

template<class T> // 只能用于奇数 
struct ExactD {
	T t, i;
	ExactD() = default;
  	ExactD(const T &n): t(T(-1) / n), i(mul_inv(n)) {}
  	constexpr static T mul_inv(T n, int e = 6, T x = 1) {
    	return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
  	}
  	friend T operator / (const T &n, const ExactD &d) { return n * d.i; }
	bool divide(const T &n) const { return n * i <= t; }
};

using FastDiv32 = FastD<uint32, uint64>;
using FastDiv64 = FastD<uint64, uint128>;
using ExactDiv32 = ExactD<uint32>;
using ExactDiv64 = ExactD<uint64>;
