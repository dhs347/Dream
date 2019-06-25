#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) -1; i >= (a); --i)
#define endl "\n"
#define pw(a) (1ll << (a))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 22;

ll lcm(ll a, ll b) {
	return a * b / __gcd(a, b);
}

struct Node {
	ll a, b;
	Node() {}
	Node(string s) {
		stringstream ss(s);
		ss >> a; b = 1;
	}
	Node(ll a, ll b) : a(a), b(b) {}
	Node operator + (const Node &c) const {
		ll t = lcm(b, c.b);
		ll z = a * (t / b) + c.a * (t / c.b);
		ll d = __gcd(t, z);
		t /= d, z /= d;
		if(t < 0) t *= -1, z *= -1;
		return Node(z, t);
	}
	Node operator - (const Node &c) const {
		ll t = lcm(b, c.b);
		ll z = a * (t / b) - c.a * (t / c.b);
		ll d = __gcd(t, z);
		t /= d, z /= d;
		if(t < 0) t *= -1, z *= -1;
		return Node(z, t);
	}
	Node operator * (const ll &c) const {
		ll z = a * c, t = b;
		ll d = __gcd(t, z);
		t /= d, z /= d;
		if(t < 0) t *= -1, z *= -1;
		return Node(z, t);
	}
	Node operator / (const ll &c) const {
		ll z = a, t = b * c;
		ll d = __gcd(t, z);
		t /= d, z /= d;
		if(t < 0) t *= -1, z *= -1;
		return Node(z, t);
	}
	bool operator == (const Node &c) const {
		return a == c.a && b == c.b;
	}
	bool operator != (const Node &c) const {
		return !(*this == c);
	}
	void print() {
		cout << a << "/" << b;
	}
};

int n, m;
bool ok[N][N], ot[N][N], ans;
Node nd[N][N], tmp[N][N];

void gao1() {
	rep(i, 0, n) {
		int cnt = 0;
		rep(j, 0, m) cnt += ot[i][j];
		if(cnt < 2) continue;
		Node d, pre, A; bool Find = 0; int pj;
		rep(j, 0, m) if(ot[i][j]) {
			if(Find) {
				d = (tmp[i][j] - pre) / (j - pj);
				A = pre - d * pj;
				break;
			} else {
				Find = 1;
				pre = tmp[i][j];
				pj = j;
			}
		}
		rep(j, 0, m) {
			if(ot[i][j]) {
				if(tmp[i][j] != A) ans = 0;
			} else {
				tmp[i][j] = A;
				ot[i][j] = 1;
			}
			A = A + d;
		}
	}
}
void print() {
	rep(i, 0, n) {
		rep(j, 0, m) {
			tmp[i][j].print();
			cout << " \n"[j == m - 1];
		}
	}
}
void gao2() {
	rep(j, 0, m) {
		int cnt = 0;
		rep(i, 0, n) cnt += ot[i][j];
		if(cnt < 2) continue;
		Node d, pre, A; bool Find = 0; int pj;
		rep(i, 0, n) if(ot[i][j]) {
			if(Find) {
				d = (tmp[i][j] - pre) / (i - pj);
				A = pre - d * pj;
				break;
			} else {
				Find = 1;
				pre = tmp[i][j];
				pj = i;
			}
		}
		rep(i, 0, n) {
			if(ot[i][j]) {
				if(tmp[i][j] != A) ans = 0;
			} else {
				tmp[i][j] = A;
				ot[i][j] = 1;
			}
			A = A + d;
		}
	}
}

void gao() {
	int pre = 0;
	while(1) {
		gao1();
		gao2();
		int cnt = 0;
		rep(i, 0, n) rep(j, 0, m) cnt += ot[i][j];
		if(cnt == pre) return ;
		pre = cnt;
	}
}
void solve(ll nn) {
	int hang[22] = {0}, lie[22] = {0};
	rep(i, 0, n) rep(j, 0, m) hang[i] += ot[i][j], lie[j] += ot[i][j];
	rep(i, 0, n) hang[i] = (hang[i] == 1);
	rep(i, 0, m) lie[i] = (lie[i] == 1);
	int x = -1, y = 0;
	rep(i, 0, n) rep(j, 0, m) if(!ot[i][j] && hang[i] && lie[j]) {
		x = i, y = j; break;
	}
	if(x == -1) rep(i, 0, n) rep(j, 0, m) if(!ot[i][j] && (hang[i] || lie[j])) {
		x = i, y = j; break;
	}
	if(x == -1) rep(i, 0, n) rep(j, 0, m) if(!ot[i][j]) {
		x = i, y = j; break;
	}
	if(x == -1) return ;
	ot[x][y] = 1;
	tmp[x][y] = Node(nn, 1);
	gao();
}
void solve0(ll nn) {
	solve(nn);
	int pre = 0;
	while(1) {
		solve(0);
		int cnt = 0;
		rep(i, 0, n) rep(j, 0, m) cnt += ot[i][j];
		if(cnt == pre) break;
		pre = cnt;
	}
	print();
}
void solve(ll n1, ll n2, ll n3, ll n4) {
	solve(n1);
	solve(n2);
	solve(n3);
	solve(n4);
	print();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	ans = 1;
	cin >> n >> m;
	rep(i, 0, n) rep(j, 0, m) {
		string s; cin >> s;
		if(s[0] == '?') {
		} else {
			ok[i][j] = 1;
			nd[i][j] = Node(s);
			ot[i][j] = 1;
			tmp[i][j] = nd[i][j];
		}
	}
	gao();
	if(!ans) {
		cout << "None" << endl;
		return 0;
	}
	int cnt = 0;
	rep(i, 0, n) rep(j, 0, m) cnt += ot[i][j];
	if(cnt == n * m) {
		cout << "Unique" << endl;
		print();
		return 0;
	}
	rep(i, 0, n) rep(j, 0, m) ok[i][j] = ot[i][j], nd[i][j] = tmp[i][j];
	cout << "Multiple" << endl;
	solve0(0);
	rep(i, 0, n) rep(j, 0, m) ot[i][j] = ok[i][j], tmp[i][j] = nd[i][j];
	cout << "and" << endl;
	solve0(1);
	return 0;
}
