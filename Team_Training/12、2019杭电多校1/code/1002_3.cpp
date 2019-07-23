#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = pw(20) + 1;
const char M = 30;

int n, m, pans;

struct Node {
	int a[M];
	char sz;
	Node() { }
	inline void add(int x) {
		for(int i = M - 1; i >= 0 && x; --i) if(x >> i & 1) {
			if(a[i]) {
				x ^= a[i];
				continue;
			}
				a[i] = x;
				++sz;
				break;
		}
	}
	inline void init() {
		fill_n(a, M, 0); sz = 0;
	}
	inline Node operator + (const Node &c) const {
		if(sz > c.sz) {
			const Node &a = *this, &b = c;	
			if(a.sz == M) return a;
			Node res = a;
			per(i, 0, M) if(b.a[i] && !a.a[i]) {
				res.add(b.a[i]);
				if(res.sz == M) return res;
			}
			return res;
		} else {
			const Node &b = *this, &a = c;	
			if(a.sz == M) return a;
			Node res = a;
			per(i, 0, M) if(b.a[i] && !a.a[i]) {
				res.add(b.a[i]);
				if(res.sz == M) return res;
			}
			return res;
		}
	}
}ans;

struct FI {
	static const int S = 1e5;
	int wpos;
	char wbuf[S];
	bool ed;
	FI() : wpos(0), ed(0) {}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if(pos == len) pos = 0, len = fread(buf, 1, S, stdin);
		if(pos == len) return -1;
		return buf[pos++];
	}
	inline int xint() {
		int c = xchar(), x = 0, s = 1;
		while(c <= 32) {
			if(!~c) return ed = 1;
			c = xchar();
		}
		for(; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x * s;
	}
	inline void wchar(int x) {
		if(wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wint(int x) {
		char s[24];
		int n = 0;
		while(x || !n) s[n++] = '0' + x % 10, x /= 10;
		while(n--) wchar(s[n]);
	}
	~FI() {
		if(wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
}io;
int cnt;
struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = (::N << 1) + 1;
	Node val[N];
	inline void init(int n) {
		rep(i, 0, n << 1) val[i].init();
	}
	inline void qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) {
			if (cnt > 10) return;
			ans = ans + val[rt];
			cnt++;
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) qry(L, R, l, mid, ls);
		if(R > mid) qry(L, R, mid + 1, r, rs);
	}
	inline void upd(int p, int c, int l, int r, int rt) {
		val[rt].add(c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
}seg;

inline void solve() {
	n = io.xint();
	m = io.xint();
	int sum = n + m;
	for(int i = 1; ; ++i) if(pw(i) >= sum) {
		sum = pw(i);
		break;
	}
	seg.init(sum);
	rep(i, 1, n + 1) {
		int x = io.xint();
		seg.upd(i, x, 1, sum, 1);
	}
	pans = 0;
	rep(i, 1, m + 1) {
		int o = io.xint();
		if(o == 0) {
			cnt = 0;
			int l = io.xint();
			int r = io.xint();
			l = (l ^ pans) % n + 1, r = (r ^ pans) % n + 1;
			if(l > r) swap(l, r);
			ans.init();
			seg.qry(l, r, 1, sum, 1);
			pans = 0;
			per(k, 0, M) if(ans.a[k]) pans ^= ans.a[k];
			io.wint(pans);
			io.wchar('\n');
		} else {
			int x = io.xint() ^ pans; 
			seg.upd(n + 1, x, 1, sum, 1);
			n++;
		}
	}
}

int main() {
	//db x = sizeof(seg) + sizeof(io);
	//de(x / 1024.);
	int T = io.xint();
	while(T--) solve();
	return 0;
}
