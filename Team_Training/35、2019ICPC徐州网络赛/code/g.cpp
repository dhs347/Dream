#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 3e5 + 100;

string s;
ll ans;
int pre[N][26];

struct PAM {
	static const int N = ::N, M = 26;
	int ne[N][M], fail[N], len[N], S[N], last, n, p, cnt[N], las[N], ed[N];
	int newnode(int l) {
		fill(ne[p], ne[p] + M, 0);
		len[p] = l;
		las[p] = n;
		cnt[p] = 0;
		return p++;
	}
	void init() {
		p = 0; newnode(0); newnode(-1);
		S[n = last = 0] = -1;
		fail[0] = 1;
	}
	int get_fail(int x) {
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c, int ind) {
		S[++n] = c;
		int cur = get_fail(last);
		if(!ne[cur][c]) {
			int now = newnode(len[cur] + 2);
			fail[now] = ne[get_fail(fail[cur])][c];
			ne[cur][c] = now;
		}
		last = ne[cur][c];
		cnt[last]++;
		ed[last] = ind;
	}
	void build() {
		for(int i = p - 1; ~i; --i) cnt[fail[i]] += cnt[i], ed[fail[i]] = ed[i];
	}
	void solve() {
		rep(i, 2, p) {
			int r = ed[i], l = r - len[i] + 1;
			rep(j, 0, 26) {
				int c = pre[r][j]; if(l) c -= pre[l - 1][j];
				if(c) ans += cnt[i];
			}
		}
	}
}pam;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	pam.init();
	rep(i, 0, sz(s)) pam.add(s[i] - 'a', i), pre[i][s[i] - 'a'] = 1;
	rep(i, 1, sz(s)) rep(j, 0, 26) pre[i][j] += pre[i - 1][j];
	pam.build();
	pam.solve();
	cout << ans << endl;
	return 0;
}
