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

const int N = 2e5 + 7;
int bn, bl[N], br[N], sz[N], BSZ, u[N], v[N], id[N], pos[N], du[N];
int T, n, m, q, op, l, r, cnt;
ll tip[2][500][1000], a[N];
vector<pii> g[N];
bool tip1[N], val[N];

// read untill EOF (xint)
struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    bool ed;
    FastIO() : wpos(0), ed(0) { }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }
    inline int xint() {
        int c = xchar(), x = 0, s = 1;
        while (c <= 32) {
            if(!~c) return ed = 1;
            c = xchar();
        }
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void xstring(char *s) {
        int c = xchar();
        while (c <= 32) c = xchar();
        for (; c >  32; c = xchar()) *s++ = c;
        *s = 0;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(int x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
    }
    inline void wstring(const char *s) {
        while (*s) wchar(*s++);
    }
    ~FastIO() {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;


void ini(int n) {
  bn = (n - 1) / BSZ + 1;
  rep(b, 0, bn) {
  	tip1[b] = 0; 
  	rep(i, 0, cnt) tip[0][b][i] = tip[1][b][i] = 0;
    bl[b] = b * BSZ;
    br[b] = min(n, (b + 1) * BSZ);
	rep(i, bl[b], br[b]) {
		id[i] = b; val[i] = 1;
		if (du[u[i]] > BSZ) tip[0][b][pos[u[i]]] ^= a[v[i]];
		if (du[v[i]] > BSZ && u[i] != v[i]) tip[0][b][pos[v[i]]] ^= a[u[i]];
	}
    sz[b] = br[b] - bl[b];
  }
}

// change [l, r) in block b : rep(b, 0, bn) chg(b, ql, qr);
void chg(int b, int l, int r) {
  int nl = max(l, bl[b]);
  int nr = min(r, br[b]);
  if (nl >= nr) return;
  if (nr - nl == sz[b]) {
    // chg whole block
    tip1[b] ^= 1;
  }
  else {
    // mybey bud(b)
    // chg [nl, nr)
    rep(i, nl, nr) {
		val[i] ^= 1;
		if (du[u[i]] > BSZ) {
			tip[0][b][pos[u[i]]] ^= a[v[i]];
			tip[1][b][pos[u[i]]] ^= a[v[i]];
		}
		if (du[v[i]] > BSZ && u[i] != v[i]) {
			tip[0][b][pos[v[i]]] ^= a[u[i]];
			tip[1][b][pos[v[i]]] ^= a[u[i]];
		}
	}
  }
}

ll get(int u) {
	ll res = 0;
	if (du[u] <= BSZ) {
		for (auto v : g[u]) if (tip1[id[v.se]] ^ val[v.se]) res ^= a[v.fi];
		return res;
	}else{
		rep(i, 0, bn) res ^= tip[tip1[i]][i][pos[u]];
		return res;
	}
}

ll rnd() {
	ll x = (rand() << 15) + rand();
	ll y = (rand() << 15) + rand();
	return (x << 30) + y;
}

int main() {
	freopen("a.in","r",stdin);
	T = io.xint(); srand(time(0));
	rep(cas, 0, T) {
		n = io.xint(); m = io.xint(); cnt = 0;
		BSZ = sqrt(m); 
		rep(i, 1, n+1) a[i] = rnd(), g[i].clear(), du[i] = 0;
		rep(i, 0, m) {
			u[i] = io.xint(); v[i] = io.xint();
			du[u[i]]++;
			if (u[i] != v[i]) du[v[i]]++; 
		}
		rep(i, 0, m) {
			if (du[u[i]] <= BSZ) g[u[i]].pb(mp(v[i], i));
			if (u[i] != v[i] && du[v[i]] <= BSZ) g[v[i]].pb(mp(u[i], i)); 
		}
		rep(i, 1, n+1) if (du[i] > BSZ) pos[i] = cnt++;
		ini(m);
		q = io.xint();
		rep(i, 0, q) {
			op = io.xint();
			l = io.xint();
			r = io.xint();
			if (op == 1) {
				l--; r--; 
				rep(b, id[l], id[r]+1) chg(b, l, r+1);
			}else {
				ll t1 = get(l), t2 = get(r);
				io.wchar((t1 == t2) + 48);
			}
		}
		io.wchar('\n');
	} 
	return 0;
}

