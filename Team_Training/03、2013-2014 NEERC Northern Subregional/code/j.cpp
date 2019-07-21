#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010, P = 1e9;

int sub(int a, int b) {
	if((a -= b) < 0) a += P;
	return a;
}
int mul(int a, int b) { return 1ll * a * b % P; }
int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}

struct Node {
	// 0: op 1:
	bool o; char ch; vi v;
	Node() {}
	Node(char ch) : o(0), ch(ch) {}
	Node(vi v) : o(1), v(v) {}
	Node operator + (const Node &c) const {
		vi vec(11);
		rep(i, 0, 11) vec[i] = add(v[i], c.v[i]);
		return Node(vec);
	}
	Node operator - (const Node &c) const {
		vi vec(11);
		rep(i, 0, 11) vec[i] = sub(v[i], c.v[i]);
		return Node(vec);
	}
	Node operator * (const Node &c) const {
		vi vec(11);
		rep(i, 0, 11) rep(j, 0, 11 - i) vec[i + j] = add(vec[i + j], mul(v[i], c.v[j]));
		return Node(vec);
	}
};

int n, a[N], pre[11], b[N];
string s;
vector<Node> rpn, ch, sta;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	freopen("j.in", "r", stdin);
	freopen("j.out", "w", stdout);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	cin >> s;
	rep(i, 0, sz(s)) {
		char c = s[i];
		if(c == '(') ch.pb(Node(c));
		else if(c == ')') {
			while(ch.back().ch != '(') rpn.pb(ch.back()), ch.pop_back();
			ch.pop_back();
		}
		else if(s[i] == '+' && (i == sz(s) - 1 || s[i + 1] != '/')) ch.pb(Node('a'));
		else if(s[i] == '-' && i && (s[i - 1] == ')' || s[i - 1] == 'X' || s[i - 1] == 'N' || ('0' <= s[i - 1] && s[i - 1] <= '9'))) ch.pb(Node('b'));
		else if(s[i] == '*' && (i == sz(s) - 1 || s[i + 1] != ':')) ch.pb(Node('c'));
		else if(s[i] == '-') ch.pb(Node('d'));
		else if(s[i] == '*') ch.pb(Node('e')), ++i;
		else if(s[i] == '+') ch.pb(Node('f')), ++i;
		else {
			vi v(11);
			if(s[i] == 'X') v[1] = 1;
			else if(s[i] == 'N') v[0] = n;
			else {
				for(; i < sz(s) && '0' <= s[i] && s[i] <= '9'; ++i) v[0] = add(mul(v[0], 10), s[i] - '0');
				--i;
			}
			rpn.pb(Node(v));
		}
	}
	reverse(all(ch));
	rpn.insert(rpn.end(), all(ch));
	rep(i, 1, n + 1) b[i] = 1;
	rep(i, 0, 11) {
		rep(j, 1, n + 1) pre[i] = add(pre[i], b[j]);
		rep(j, 1, n + 1) b[j] = mul(b[j], a[j]);
	}
	for(auto u : rpn) {
		if(u.o) sta.pb(u);
		else {
			if(u.ch == 'a') {
				auto b = sta.back(); sta.pop_back();
				sta[sz(sta) - 1] = sta.back() + b;
			}
			else if(u.ch == 'b') {
				auto b = sta.back(); sta.pop_back();
				sta[sz(sta) - 1] = sta.back() - b;
			}
			else if(u.ch == 'c') {
				auto b = sta.back(); sta.pop_back();
				sta[sz(sta) - 1] = sta.back() * b;
			}
			else if(u.ch == 'd') {
				auto &a = sta[sz(sta) - 1].v;
				rep(i, 0, 11) a[i] = (a[i] ? P - a[i] : 0);
			}
			else if(u.ch == 'e') {
				sta[sz(sta) - 1] = sta.back() * sta.back();
			}
			else if(u.ch == 'f') {
				auto &a = sta[sz(sta) - 1].v;
				int val = 0;
				rep(i, 0, 11) val = add(val, mul(a[i], pre[i]));
				vi v(11); v[0] = val;
				sta[sz(sta) - 1] = Node(v);
			}
		}
	}
	cout << sta[0].v[0] << endl;
	return 0;
}
