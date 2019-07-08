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
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, d[200], a[5][20], cnt, ok, w[10], num;
set<string> M;
string s;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	n = 14;
	d['s'] = 0;
	d['p'] = 1;
	d['w'] = 2;
	rep(i, 0, n) {
		cin >> s;
		if (s[0] >= '0' && s[0] <= '9') {
			a[d[s[1]]][s[0] - '0']++;
			w[d[s[1]]]++;
		}else {
			M.insert(s);
			cnt++;
		}
	}
	rep(i, 0, 3) if (w[i] == 14){
		ok = 1;
		rep(j, 2, 9) ok &= (a[i][j] > 0);
		ok &= (a[i][1] >= 3);
		ok &= (a[i][9] >= 3);
		if (ok) {
			cout << "jiulianbaodeng!" << endl;
			return 0;
		}
	}
	if (sz(M) >= 7) {
		ok = 1;num = 0;
		rep(i, 0, 3) ok &= a[i][1] > 0, ok &= a[i][9] > 0, num += a[i][1] + a[i][9];
		ok &= (cnt > 7 || num > 6);
		if (ok) {
			cout << "shisanyao!" << endl;
			return 0;
		}
	}
	cout << "I dont know!" << endl;
	return 0;
}
