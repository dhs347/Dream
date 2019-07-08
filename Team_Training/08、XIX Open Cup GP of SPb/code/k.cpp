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

const int N = 222;

int n, m;
int arr[N][N], ord[N][N];
bool vis[N][N];

ll lcm(ll a, ll b) { return a * b / __gcd(a, b); }
struct Node {
	ll a, b;
	Node() : a(0), b(1) {}
	Node(string s) {
		stringstream ss(s);
		ss >> a; b = 1;
	}
	Node(ll c) : a(c), b(1) {}
	Node(ll _a, ll _b) {
		a = _a, b = _b;
		ll d = __gcd(a, b);
		a /= d, b /= d;
		if(b < 0) a = -a, b = -b;
	}
	Node operator + (const Node &c) const {
		ll t = lcm(b, c.b);
		ll z = a * (t / b) + c.a * (t / c.b);
		return Node(z, t);
	}
	Node operator - (const Node &c) const {
		ll t = lcm(b, c.b);
		ll z = a * (t / b) - c.a * (t / c.b);
		return Node(z, t);
	}
	Node operator * (const Node &c) const { return Node(a * c.a, b * c.b); }
	Node operator / (const Node &c) const { return Node(a * c.b, b * c.a); }
	Node operator * (const ll &c) const { return Node(a * c, b); }
	Node operator / (const ll &c) const { return Node(a, b * c); }
	bool operator == (const Node &c) const { return a == c.a && b == c.b; }
	bool operator != (const Node &c) const { return !(*this == c); }
	void print() { cout << a << "/" << b; }
};

Node a[N][N], x[N], ta[N][N], tx[N];
bool ok[N];
int equ, var;
int fre[N], cfre;

void gao(int p[], int q[]) {
	int val[3] = {-2, 1, 1};
	rep(i, 0, 3) {
		int nx = p[i], ny = q[i];
		if(vis[nx][ny]) {
			a[equ][var] = a[equ][var] - Node(arr[nx][ny]) * val[i];
		} else {
			a[equ][ord[nx][ny]] = Node(val[i]);
		}
	}
	++equ;
}
void solve(int c, int k, int col, int p) {
	int pre = var;
	per(i, 0, k) {
		int num = 0;
		rep(j, 0, var) if(a[i][j].a) {
			if(!num) p = j; num++;
		}
		rep(j, 0, i) if(a[j][p].a) {
			Node t = a[j][p];
			rep(l, p, var + 1) a[j][l] = a[j][l] - a[i][l] * t;
			//per(l, p, var + 1) a[j][l] = a[j][l] - a[i][l] * a[j][p];
		}
		rep(j, p + 1, pre) fre[cfre++] = j, x[j] = Node(c); pre = p;
		x[p] = a[i][var];
		rep(j, p + 1, var) x[p] = x[p] - x[j] * a[i][j];
		ok[p] = 1;
	}
	if(!k) rep(i, 0, var) x[i] = Node(c);
	rep(i, 0, n) rep(j, 0, m) {
		(vis[i][j] ? Node(arr[i][j]) : x[ord[i][j]]).print();
//		if(!vis[i][j]) dd(ord[i][j]), x[ord[i][j]].print();
		cout << " \n"[j == m - 1];
	}
}
void gauss() {
	int k, col, p;
	for(k = col = 0; k < equ && col < var; ++k, ++col) {
		p = k; rep(i, k + 1, equ) if(a[i][col].a) { p = i; break; }
		if(p != k) rep(j, k, var + 1) swap(a[p][j], a[k][j]);
		if(!a[k][col].a) { k--; continue; }
		per(i, col, var + 1) a[k][i] = a[k][i] / a[k][col];
		rep(i, k + 1, equ) if(a[i][col].a) {
			per(j, col, var + 1) a[i][j] = a[i][j] - a[k][j] * a[i][col];
		}
	}
	rep(i, k, equ) if(a[i][var].a) {
		cout << "None" << endl;
		exit(0);
	}
	if(k == var) {
		cout << "Unique" << endl;
		per(i, 0, var) {
			Node t = a[i][var];
			rep(j, i + 1, var) if(a[i][j].a) t = t - a[i][j] * x[j];
			x[i] = t;
		}
		rep(i, 0, n) rep(j, 0, m) {
			(vis[i][j] ? Node(arr[i][j]) : x[ord[i][j]]).print();
			cout << " \n"[j == m - 1];
		}
		exit(0);
	}
	cout << "Multiple" << endl;
	rep(i, 0, equ) rep(j, 0, var + 1) ta[i][j] = a[i][j];
	rep(i, 0, var) tx[i] = x[i];
	solve(0, k, col, p);
	cout << "and" << endl;
	memset(ok, 0, sizeof(ok));
	memset(fre, cfre = 0, sizeof(fre));
	rep(i, 0, equ) rep(j, 0, var + 1) a[i][j] = ta[i][j];
	rep(i, 0, var) x[i] = tx[i];
	solve(1, k, col, p);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 0, n) rep(j, 0, m) {
		string s; cin >> s;
		if(s[0] == '?') {
			ord[i][j] = var++;
		} else {
			vis[i][j] = 1;
			stringstream ss(s);
			ss >> arr[i][j];
		}
	}
	rep(i, 0, n) rep(j, 0, m) {
		int p[3] = {i, i + 1, i - 1};
		int q[3] = {j, j, j};
		if(i - 1 >= 0 && i + 1 < n) gao(p, q);
		p[1] = p[2] = i;
		q[1] = j + 1, q[2] = j - 1;
		if(j - 1 >= 0 && j + 1 < m) gao(p, q);
	}
	gauss();
	return 0;
}
