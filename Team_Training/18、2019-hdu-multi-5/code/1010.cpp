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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010, inf = 1e9; 

int n, a[N], st[N], ed[N], val[N];
bool vis[N];
vi vec[N];

struct Seg {
	#define ls rt << 1
	#define rs ls | 1
	static const int N = ::N << 2;
	int mi[N];
	void build() {
		fill_n(mi, n << 2 | 1, inf); 
	}
	void upd(int p, int c, int l = 1, int r = n, int rt = 1) {
		mi[rt] = min(mi[rt], c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
	int qry(int c, int l = 1, int r = n, int rt = 1) {
		if(l == r) return l * (mi[rt] < c);
		int mid = l + r >> 1;
		if(mi[rs] < c) return qry(c, mid + 1, r, rs);
		else return qry(c, l, mid, ls);
	}
}seg[2];

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	rep(o, 0, 2) seg[o].build();
	rep(i, 1, n + n + 1) st[i] = ed[i] = val[i] = vis[i] = 0, vec[i].clear();
	rep(i, 1, n + 1) {
		int x = abs(a[i]);
		ed[x] = i + n - 1;
		int t = max(seg[0].qry(x), seg[1].qry(-x));
		t = t ? t + n : 1;
		st[x] = t;
		seg[a[i] < 0].upd(i, a[i]);
	}
	rep(i, 1, n + n + 1) if(!ed[i]) {
		ed[i] = n + n;
		int x = i; 
		int t = max(seg[0].qry(x), seg[1].qry(-x));
		t = t ? t + n : 1;
		st[x] = t;
	}
	rep(i, 1, n + n + 1) val[ed[i]] = i, vec[st[i]].pb(i);//, dd(i), dd(st[i]), de(ed[i]);
	vi ans;
	priority_queue<int> que;
	rep(i, 1, n + n + 1) {
		for(auto u : vec[i]) que.push(-u); 
		if(val[i] && !vis[val[i]]) {
			ans.pb(val[i]);
			vis[val[i]] = 1;
		} else {
			int res = 0;
			while(!que.empty()) {
				auto t = -que.top(); que.pop();
				if(!vis[t]) {
					res = t;
					break;
				}
			}
			if(!res) {
				cout << -1 << endl;
				return ;
			}
			ans.pb(res);
			vis[res] = 1;
		}
	}
	rep(i, 0, n + n) cout << ans[i] << " \n"[i == sz(ans) - 1];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
//	freopen("1.in", "r", stdin);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
/*
1
3
-1 4 -2

4
3
-1 4 -2
1
2
2
-4 3
4
-2 8 6 -3
*/
