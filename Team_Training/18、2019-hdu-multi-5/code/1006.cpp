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

void ex(char *s, int *z, char *t, int *p) {
	int lens = strlen(s);
	int lent = strlen(t);
	p[0] = 0;
	for(int i = 0, x = 0, y = 0; i < lens; ++i) {
		z[i] = i <= y ? min(y - i, p[i - x]) : 0;
		while(i + z[i] < lens && z[i] < lent && s[i + z[i]] == t[z[i]]) ++z[i];
		if(y <= i + z[i]) x = i, y = i + z[i];
	}
}

const int N = 1e6 + 7;

char t[N];
int nt[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) {
		cin >> t;
		int n = strlen(t);
		ex(t + 1, nt + 1, t, nt);
		ll ans = 0;
		rep(i, 1, n) {
			ans += nt[i];
			if(nt[i] != n - i) ans++;
		}
		cout << ans << endl;
		//rep(i, 0, n) dd(i), de(nt[i]);
		//cout << endl;
	}
	return 0;
}
