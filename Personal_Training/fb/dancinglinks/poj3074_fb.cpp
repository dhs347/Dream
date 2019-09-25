#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
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
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

struct DLX{
#define FOR(i, ne, t) for(int i = ne[t]; i != t; i = ne[i])
	static const int N = 1e4 + 8;
	int n, m, tim, ansd;
	int row[N], col[N], s[N], ans[N];
	int l[N], r[N], u[N], d[N];
	pair<pii, int> pos[N];
	string ss;
	void init(int _m) {
		m = _m;
		rep(i, 0, m+1) l[i] = i-1, r[i] = i+1, u[i] = d[i] = i;
		l[0] = m, r[m] = 0, tim = m+1;
		rep(i, 0, m+1) s[i] = 0; 
	}
	void add(int R, const vi &tmp){
		int first = tim;
		rep(i, 0, sz(tmp)) {
			int c = tmp[i];
			l[tim] = tim-1, r[tim] = tim+1, u[tim] = u[c], d[tim] = c;
			u[c] = tim; d[u[tim]] = tim;
			row[tim] = R, col[tim] = c;
			tim++, s[c]++;
		}
		if (sz(tmp)) l[first] = tim-1, r[tim-1] = first;
	}
	inline void remove(int c) {
		l[r[c]] = l[c];
		r[l[c]] = r[c];
		FOR(i, d, c)
			FOR(j, r, i) u[d[j]] = u[j], d[u[j]] = d[j], --s[col[j]];
	}
	inline void restore(int c) {
		FOR(i, u, c)
			FOR(j, l, i) u[d[j]] = j, d[u[j]] = j, ++s[col[j]];
		 l[r[c]] = c;
		 r[l[c]] = c;
	}
	bool dance(int dep) {
		if (!r[0]) return ansd = dep, 1;
		int c = r[0];
		FOR(i, r, 0) if (s[c] > s[i]) c = i;
		remove(c);
		FOR(i, d, c) {
			ans[dep] = row[i];
			FOR(j, r, i) remove(col[j]);
			if (dance(dep+1)) return 1;
			FOR(j, l, i) restore(col[j]);
		}
		restore(c);
		return 0;
	}
	vi tmp;
	void ins(int x, int y, int c) {
		n++; pos[n] = mp(mp(x, y), c);
		int p = ((x - 1) / 3 * 3 + (y - 1) / 3) * 9 + c;
		tmp[0] = ((x - 1) * 9 + y);
		tmp[1] = (81 * 1 + (x - 1) * 9 + c);
		tmp[2] = (81 * 2 + (y - 1) * 9 + c);
		tmp[3] = (81 * 3 + p);
		add(n, tmp);
	} 
	
	void work() {
		while(cin >> ss) {
			tmp.resize(4);
			n = 0; if (ss == "end") return;
			init(81 * 4);
			rep(i, 0, sz(ss)) {
				int x = i / 9 + 1, y = i % 9 + 1;
				if (ss[i] == '.') {
					rep(i, 1, 10) ins(x, y, i);
				}else ins(x, y, ss[i] - '0');
			}
	    	bool flag = dance(1);
	    	if (flag) {
				rep(i, 1, ansd) {
					//cout << ans[i] << " \n"[i == ansd - 1];
					int x = pos[ans[i]].fi.fi, y = pos[ans[i]].fi.se, c = pos[ans[i]].se;
					ss[(x - 1) * 9 + y - 1] = c + '0';
				}
				cout << ss << endl;
			}	
			else cout << "No Solution!" << endl; 
		}
	}
} T;

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	T.work();
	return 0;
}


