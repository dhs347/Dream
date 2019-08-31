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
#define endl '\n'
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e7;

struct Node {
	vi val, son; int fa, ord;
	void clear() {
		val.clear(); son.clear();
	}
}nd[N];

int L, rt; vi sta;

int newnode() {
	int u = 0;
	if(sz(sta)) {
		u = sta.back();
		sta.pop_back();
	} else {
		u = L++;
	}
	nd[u].clear();
	return u;
}

void gao(int u) {
	rep(i, 0, sz(nd[u].son)) {
		int v = nd[u].son[i];
		nd[v].fa = u;
		nd[v].ord = i;
	}
}
void add(int u, int x, int o = 0) {
	if(sz(nd[u].val) == 3 && !o) {
		int a = newnode(), b = newnode(), c = newnode();
		nd[a].val.pb(nd[u].val[1]);
		nd[b].val.pb(nd[u].val[0]);
		nd[c].val.pb(nd[u].val[2]);
		nd[a].son.pb(b); nd[a].son.pb(c); gao(a);
		if(sz(nd[u].son)) {
			nd[b].son.pb(nd[u].son[0]);
			nd[b].son.pb(nd[u].son[1]);
			nd[c].son.pb(nd[u].son[2]);
			nd[c].son.pb(nd[u].son[3]);
			gao(b), gao(c);
		}
		if(u == rt) {
			sta.pb(u);
			rt = a;
			add(a, x, 1);
		} else {
			int fa = nd[u].fa, ord = nd[u].ord;
			//	for(auto t : nd[fa].val) de(t);
			nd[fa].val.insert(nd[fa].val.begin() + ord, all(nd[a].val));
			//for(auto t : nd[fa].val) de(t);
			nd[fa].son[ord] = nd[a].son[0];
			nd[fa].son.insert(nd[fa].son.begin() + ord + 1, nd[a].son[1]);
			/*
				 de(1);
				 for(auto s : nd[fa].son) {
				 for(auto t : nd[s].val) cout << t << " " ;cout << endl;
				 }
				 de(1);
			 */
			//			de(sz(nd[fa].son));
			gao(fa);
			sta.pb(a);
			add(fa, x, 1);
		}
	} else if(sz(nd[u].son) == 0) {
		nd[u].val.pb(x);
		sort(all(nd[u].val));
	} else {
		bool ok = 1;
		rep(i, 0, sz(nd[u].val)) if(nd[u].val[i] > x) {
			ok = 0;
			add(nd[u].son[i], x);
			break;
		}
		if(ok) add(nd[u].son.back(), x);
	}
}

void dfs(int u) {
	rep(i, 0, sz(nd[u].val)) cout << nd[u].val[i] << " \n"[i == sz(nd[u].val) - 1];
	for(auto v : nd[u].son) dfs(v);
}

void solve() {
	int n; cin >> n;
	L = 0; sta.clear();
	rt = newnode();
	rep(i, 1, n + 1) {
		int x; cin >> x; 
		//	cout << "==============" << endl;
		//de(x);
		add(rt, x);
		//dfs(rt); 
		//cout << endl;
	}
	dfs(rt);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ":" << endl;
		solve();
	}
	return 0;
}
