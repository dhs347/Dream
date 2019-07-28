#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;

string s; int P, Q; ll f[N];

struct SAM {
	static const int N = ::N << 1, M = 26;
	int par[N], l[N], ne[N][M];
	int rt, last, L;
	void add(int c) {
		int p = last, np = ++L;
		fill(ne[np], ne[np] + M, 0);
		l[np] = l[p] + 1;
		last = np;
		while(p && !ne[p][c]) ne[p][c] = np, p = par[p];
		if(!p) par[np] = rt;
		else{
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
	void ini() {
		rt = last = L = 1;
		fill(ne[rt], ne[rt] + M, 0);
		l[0] = -1;
	}
	void solve() {
		ini();
		int n = sz(s), p = rt, j = 0;
		rep(i, 1, n + 1) {
			int c = s[i - 1] - 'a';
			f[i] = f[i - 1] + P;
			while(j + 1 < i && !ne[p][c]) {
				add(s[j++] - 'a');
				while(p != rt && j + l[par[p]] + 1 > i - 1) p = par[p];
			}
			p = ne[p][c] ? ne[p][c] : rt;
			while(p != rt && j + l[par[p]] + 1 > i) p = par[p];
			int t = i - min(l[p], i - j);
			if(t < i) f[i] = min(f[i], f[t] + Q);
		}
		cout << f[n] << endl;
	}
}sam;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> s >> P >> Q) sam.solve();
	return 0;
}
