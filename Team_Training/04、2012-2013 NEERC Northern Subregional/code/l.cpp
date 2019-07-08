#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 30303 * 4, M = 27;

struct Node {
	int col[M], cnt, sz, ls, rs, c; ll r;
};
int rt, L; Node nd[N];
ll Rand() {
	return ((rand() * 1ll << 32) ^ (rand() * 1ll << 16) ^ rand());
}
int newnode(int c, int len) {
	if(len == 0 || c == -1) return 0;
	nd[++L].r = Rand();
	nd[L].c = c;
	rep(i, 0, M) nd[L].col[i] = 0;
	nd[L].col[c] = nd[L].cnt = nd[L].sz = len;
	nd[L].ls = nd[L].rs = 0;
	return L;
}
void up(int x) {
	if(!x) return;
	int ls = nd[x].ls, rs = nd[x].rs;
	rep(i, 0, M) nd[x].col[i] = nd[ls].col[i] + nd[rs].col[i]; 
	nd[x].col[nd[x].c] += nd[x].cnt;
	nd[x].sz = nd[ls].sz + nd[rs].sz + nd[x].cnt;
}
int merge(int x, int y) {
	if(x && y) {
		if(nd[x].r < nd[y].r) {
			nd[x].rs = merge(nd[x].rs, y); up(x); return x;
		} else {
			nd[y].ls = merge(x, nd[y].ls); up(y); return y;
		}
	} else {
		return x + y;
	}
}
void split(int u, int k, int &x, int &y) {
	if(u) {
		int sz = nd[nd[u].ls].sz + nd[u].cnt;
		if(sz < k) {
			x = u, split(nd[u].rs, k - sz, nd[u].rs, y);
		} else {
			y = u, split(nd[u].ls, k, x, nd[u].ls);
		}
		up(u);
	} else {
		x = y = 0;
	}
}
int Get(int u) {
	while(nd[u].ls) u = nd[u].ls;
	return nd[u].cnt + 1;
}

void print() {
	de(rt);
	rep(i, 1, L + 1) dd(i), dd(nd[i].ls), dd(nd[i].rs), de(nd[i].cnt);
	cout << endl;
}
void pp(int x) {
	de(x);
	rep(i, 0, M) if(nd[x].col[i]) cout << i << " ";cout << endl;
	cout << endl;
}

int main() {
	freopen("log.in", "r", stdin);
	freopen("log.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		string o; int x, y;
		cin >> o >> x >> y;
		if(o[0] == '+') {
			cin >> o;
			int ch = o[0] - 'a';
			int a, b, c;
			split(rt, x, a, b);
			int cnt = Get(b);
			split(b, cnt, b, c);
			int col = -1;
			rep(i, 0, M) if(nd[b].col[i] > 0) col = i;
			int b1 = newnode(col, x - 1 - nd[a].sz);
			int b3 = newnode(col, nd[a].sz + nd[b].sz - (x - 1));
			int b2 = newnode(ch, y);
			b = merge(b1, merge(b2, b3));
			rt = merge(a, merge(b, c));
		} else if(o[0] == '-') {
			int a, b, c;
			split(rt, x, a, b);
			int cnt = Get(b);
			split(b, cnt, b, c);
			int col = -1;
			rep(i, 0, M) if(nd[b].col[i]) col = i;
			int b1 = newnode(col, x - 1 - nd[a].sz);
			int b2 = newnode(col, nd[a].sz + nd[b].sz - (x - 1));
			int a0 = merge(a, b1);
			rt = merge(b2, c);
			split(rt, y, a, b);
			cnt = Get(b);
			split(b, cnt, b, c);
			col = -1; rep(i, 0, M) if(nd[b].col[i]) col = i;
			b = newnode(col, nd[a].sz + nd[b].sz - y);
			rt = merge(b, c);
			rt = merge(a0, rt);
		} else {
			y = y - x + 1;
			int a, b, c;
			split(rt, x, a, b);
			int cnt = Get(b);
			split(b, cnt, b, c);
			int col = -1;
			rep(i, 0, M) if(nd[b].col[i]) col = i;
			int b1 = newnode(col, x - 1 - nd[a].sz);
			int b2 = newnode(col, nd[a].sz + nd[b].sz - (x - 1));
			int a0 = merge(a, b1);
			rt = merge(b2, c);
			split(rt, y, a, b);
			cnt = Get(b);
			split(b, cnt, b, c);
			col = -1; rep(i, 0, M) if(nd[b].col[i]) col = i;
			int ans = merge(a, b), res = 0;
			rep(i, 0, M) res += (nd[ans].col[i] > 0);
			cout << res << endl;
			rt = merge(ans, c);
			rt = merge(a0, rt);
		}
	}
	return 0;
}
