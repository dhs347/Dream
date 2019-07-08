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
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010, P = 1e9 + 7;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}


int n, top;
int sta[N];
string str;
vi a;
vector<char> s, stack;
vector<vi> v;

bool isdig(char c) {
	return '0' <= c && c <= '9';
}

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) {
		int x;
		cin >> x;
		a.pb(x);
	}
	cin >> str;
	for(int i = 0; i < sz(str); ) {
		if(str[i] == 'X') {
			s.pb((char)('0' + sz(v)));
			v.pb(a);
			++i;
		} else if(str[i] == 'N') {
			s.pb((char)('0' + sz(v)));
			v.pb(vi(1, N));
			++i;
		} else if(isdig(str[i])) {
			int val = 0;
			while(i < sz(str) && isdig(str[i])) {
				val = add(mul(val, 10), str[i] - '0');
				++i;
			}
			s.pb((char)('0' + sz(v)));
			v.pb(vi(1, val));
		} else {
			s.pb(str[i]);
			++i;
		}
	}
	int p = sz(s) - 1;
	return 0;
}
