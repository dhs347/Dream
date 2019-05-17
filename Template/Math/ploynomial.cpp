template<class T>
struct polynomial{
	static const int N = 101010;
	static const int P = 998244353;
	T a1[N], b1[N], c[N], a[N], pre[N], suf[N], ifac[N], fac[N];
	T add(T a, T b) {a = (a + b) % P; return a < 0 ? a + P : a;}
	T mul(T a, T b) {a = 1ll * a * b % P; return a < 0 ? a + P : a;}
	T kpow(T a, T b) {T r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
	void calc(int n, T *a, T *b) {
		fill_n(c, n+1, 0);
		rep(i, 0, n+1)	rep(j, 0, 2) c[i+j] = add(c[i+j], mul(a[i], b[j]));
		memcpy(a, c, sizeof(a[0]) * (n+1));
	} 
	void solve(int n, T *x, T *y){ // a[0]*x^0 ... a[n]*x^n
		fill_n(a, n+1, 0);
		rep(i, 0, n+1) {
			fill_n(a1, n+1, 0); a1[0] = 1;
			rep(j, 0, n+1) if (j != i) a1[0] = mul(a1[0], x[i] - x[j]);
			a1[0] = mul(y[i], kpow(a1[0], P - 2));
			rep(j, 0, n+1) if (j != i) {
				b1[0] = -x[j]; b1[1] = 1;
				calc(n, a1, b1);
			}
			rep(j, 0, n+1) a[j] = add(a[j], a1[j]);
		}
	}
	T get(int n, int k, T *x, T *y) { // f(k)
		T res = 0;
		rep(i, 0, n+1) {
			T s1 = y[i], s2 = 1;
			rep(j, 0, n+1) if (j != i) s1 = mul(s1, k - x[j]);
			rep(j, 0, n+1) if (j != i) s2 = mul(s2, x[i] - x[j]);
			res = add(res, mul(s1, kpow(s2, P - 2)));
		}
		return res;
	}
	T get(int n, int k, T *y) { // x is [1..n]
		fac[0] = 1;rep(i, 1, n+1) fac[i] = mul(fac[i-1], i);
		ifac[n] = kpow(fac[n], P - 2);
		per(i, 0, n) ifac[i] = mul(ifac[i+1], i+1);
		pre[0] = suf[n+1] = 1;
		rep(i, 1, n+1) pre[i] = mul(pre[i-1], k - i);
		per(i, 1, n+1) suf[i] = mul(suf[i+1], k - i);
		T ans=0;
		rep(i, 1, n+1){
			T s1 = mul(pre[i-1], suf[i+1]);
			T s2 = mul(ifac[i-1], ifac[n-i]);
			T fg = (n-i)&1 ? -1 : 1;
			ans = add(ans, mul(fg*s1, mul(s2, y[i])));
		}
		return ans;
	}
};
