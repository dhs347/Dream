#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 1e5;
int n, m;
string s1, s2;
int ne[N][26], ans, now;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> s1 >> s2;
	n = sz(s1);
	m = sz(s2);
	s1 = " " + s1;
	s2 = " " + s2;
	rep(i, 0, 26) ne[n][i] = n + 1;
	per(i, 0, n) rep(j, 0, 26) if (s1[i+1] == j + 'a') ne[i][j] = i + 1;else ne[i][j] = ne[i+1][j];
	now = 0;
	ans = -1;
	rep(i, 1, m+1) {
		int mi = pw(30);
		rep(j, s2[i]+1, 'z'+1) mi = min(mi, ne[now][j - 'a']);
		if (mi <= n) ans = max(ans, n - mi + 1 + i - 1);
		now = ne[now][s2[i] - 'a'];
		if (now > n) break;
	
	}
	if (now < n) ans = max(ans, n - now + m);
	cout << ans << endl;
	return 0;
}
