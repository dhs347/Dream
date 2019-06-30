#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int add(int a, int b) {
	a = (a + b) % 360;
	return a < 0 ? a + 360 : a;
}

char get(int a, int b) {
	if (add(b, -60) == a) return 'l';
	if (add(b, 60) == a) return 'r';
	if (add(b, 180) == a) return 'b';
}

const int N = 1e5 + 7;
int a[N], b[N];
string s, t;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	rep(i, 1, sz(s)+1) if (s[i-1] == 'l') a[i] = add(a[i-1], -60);
	else if (s[i-1] == 'r') a[i] = add(a[i-1], 60);
	else a[i] = add(a[i-1], 180);
	rep(i, 1, sz(s)+1) b[i] = add(a[i], 180);
	t += 'b';
	per(i, 1, sz(s)) t += get(b[i], b[i+1]);
	cout << t << endl;
	return 0;
}
