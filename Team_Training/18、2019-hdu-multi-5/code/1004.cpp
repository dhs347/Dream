#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, c;

struct Node {
	ll a, b;
	void gao() {
		ll g = __gcd(a, b);
		a /= g, b /= g;
		if(b < 0) a = -a, b = -b;
	}
	Node() : a(0), b(0) {}
	Node(ll a, ll b) : a(a), b(b) {
		gao();
	}
	bool operator < (const Node &c) const {
		return (__int128)a * c.b < (__int128)c.a * b;
	}
	void print() {
		cout << a << "/" << b;
	}
	bool operator == (const Node &c) const {
		return a == c.a && b == c.b;
	}
};

struct Line {
	ll a, b; Node z;
	void read() {
		cin >> a >> b;
		z = Node(-b, a);
	}
	bool operator < (const Line &c) const {
		return z < c.z;
	}
}l[N];

bool ok;
vector<Node> ans;
void solve(Node st, Node ed, bool os, bool oe, ll a, ll b) {
//	st.print(); cout << " ";
//	ed.print(); cout << " ";
//	dd(os), de(oe);
	if(a == 0) {
		if(b == c) {
			if(!os || !oe || st < ed) {
				ok = 0;
			} else {
				ans.pb(st);
			}
		}
		return ;
	}
	Node res = Node(c - b, a);
	bool o = 1;
	if(os && res < st) o = 0;
	if(oe && ed < res) o = 0;
	if(o) ans.pb(res);
}
void solve() {
	cin >> n >> c;
	ll a = 0, b = 0;
	rep(i, 1, n + 1) l[i].read(), a -= l[i].a, b -= l[i].b;
	sort(l + 1, l + 1 + n);
	ans.clear();
	ok = 1;
	solve(Node(), l[1].z, 0, 1, a, b);
	rep(i, 1, n + 1) {
		if(!ok) break;
		a += l[i].a * 2;
		b += l[i].b * 2;
		if(i < n) solve(l[i].z, l[i + 1].z, 1, 1, a, b);
		else solve(l[i].z, Node(), 1, 0, a, b);
	}
	sort(all(ans));
	ans.erase(unique(all(ans)), ans.end());
	if(ok) {
		cout << sz(ans);
		rep(i, 0, sz(ans)) cout << " ", ans[i].print();
		cout << endl;
	} else {
		cout << -1 << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
