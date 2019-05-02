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

const int N = 1000;
string s[N], t;
int n, m, a[N], cnt, p, no;
pii b[N];
bool cmp(pii a, pii b) {
	if (a.fi != b.fi) return a.fi > b.fi;
	return a.se < b.se;
}

int main() {
	freopen("bad.in", "r", stdin);
	freopen("bad.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cout << setiosflags(ios :: fixed);
	cout  << setprecision(2);
	cin >> n >> m;
	rep(i, 1, n+1) {
		cin >> s[i];
	}
	rep(i, 1, m+1) {
		cin >> t;
		cnt  = 0; 
		rep(i, 0, sz(t)) if (t[i] == 'X') cnt++, p = i + 1;
		if (cnt == 1) a[p]++;else no++;
	}
	rep(i, 1, n+1) b[i] = mp(a[i], i);
	sort(b+1, b+n+1, cmp);
	rep(i, 1, n+1) cout << s[b[i].se] << " " << round(1.0 * b[i].fi / m * 10000) / 100 << "%" << endl;
	cout << "Invalid " << round(1.0 * no / m * 10000) / 100 << "%" << endl;
}
