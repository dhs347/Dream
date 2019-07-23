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

const int N = 202020;

string s;
int p, q, len[N], n;

struct SAM {
	static const int N = ::N << 1, M = 26;
	int par[N], l[N], ne[N][M];
	int rt, last, L;
	int cnt[N], cur[N], rig[N];
	void add(int c) {
		int p = last, np = ++L;
		fill(ne[np], ne[np] + M, 0);
		l[np] = l[p] + 1;
		last = np;
		while(p && !ne[p][c]) ne[p][c] = np, p = par[p];
		if(!p) par[np] = rt;
		else {
			int q = ne[p][c];
			if(l[q] == l[p] + 1) par[np] = q;
			else {
				int nq = ++L;
				l[nq] = l[p] + 1;
				copy(ne[q], ne[q] + M, ne[nq]);
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && ne[p][c] == q) ne[p][c] = nq, p = par[p];
			}
		}
	}
	void init() {
		rt = last = L = 1;
		fill(ne[rt], ne[rt] + M, 0);
		l[0] = -1;
	}
	void build() {
		rep(i, 0, L + 1) cnt[i] = 0;
		rep(i, 1, L + 1) ++cnt[l[i]];
		rep(i, 1, L + 1) cnt[i] += cnt[i - 1];
		rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
		rep(i, 0, L + 1) rig[i] = n + 1;
		int p = rt;
		rep(i, 0, sz(s)) {
			int c = s[i] - 'a';
			p = ne[p][c];
			rig[p] = i;
		}
		per(i, 1, L + 1) {
			int u = cur[i], fa = par[u];
			rig[fa] = min(rig[fa], rig[u]);
		}
	}
}sam;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> s >> p >> q) {
		sam.init();
		n = sz(s);
		fill_n(len, n, 0);
		for(auto c : s) sam.add(c - 'a');
		sam.build();
	}
	return 0;
}
