#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 5e5 + 5;

int n;
ll ans;
char s[N];

/*
 * [0,L] , 0 is virtual , 1 is rt , init!!
 * [l[par[s]] + 1, l[s]] 
 * 好像暴力向上跳的复杂度是对的。
 */ 
struct SAM {
	static const int N = ::N << 1, M = 26;
	int par[N], l[N], ne[N][M], cnt[N], cur[N], bla[N];
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
		rep(i, 1, L + 1) ++cnt[l[i]];
		rep(i, 1, L + 1) cnt[i] += cnt[i - 1];
		rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
		int p = rt;
		rep(i, 1, n + 1) {
			p = ne[p][s[i] - 'a'];
			++bla[p];
		}
		rep(i, 1, L + 1) {
			cnt[i] = bla[i];
			if(cnt[i] >= 2) ans += cnt[i] * 1ll * (cnt[i] - 1) / 2 * l[i];
		}
		per(i, 1, L + 1) {
			int u = cur[i];
			int fa = par[u];
			ans += cnt[fa] * 1ll * cnt[u] * l[fa];
			cnt[fa] += cnt[u];
		}
	}
}sam;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> (s + 1);
	n = strlen(s + 1);
	reverse(s + 1, s + 1 + n);
	sam.ini();
	rep(i, 1, n + 1) sam.add(s[i] - 'a');
	sam.solve();
	ans *= -2;
	rep(i, 1, n + 1) {
		ans += (n - i + 1) * 1ll * (n - 1);
	}
	cout << ans << endl;
	return 0;
}
