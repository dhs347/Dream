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
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n = 6;
char s[][7] = {
"ABABBA",
"ABBAAB",
"AABABA",
"BABBAA",
"BBAAAA",
"AAABAB"};
/*
char s[][7] = {
	"AAAAAA",
	"BBBBBB",
	"AAABBB",
	"ABABAB",
	"BABABA",
	"BBAAAA"
};
*/
char t[6][6];
vi ans[2];

void solve1(vi &ans) {
	ans = vi(n);
	rep(i, 0, n) ans[i] = i;
	do {
		bool ok = 1; int cnt;
		rep(i, 0, n) {
			int j = ans[i]; cnt = 0;
			rep(k, 0, n) cnt += (t[i][k] != s[j][k]);
			if(cnt > 1) {
				ok = 0;
				break;
			}
		}
		if(ok) {
			return ;
		}
	} while(next_permutation(all(ans)));
	ans.clear();
}

void solve2(vi &ans) {
	ans = vi(n);
	rep(i, 0, n) ans[i] = i;
	do {
		bool ok = 1;
		rep(i, 0, n) {
			int j = ans[i], cnt = 0;
			rep(k, 0, n) cnt += (t[k][i] != s[k][j]);
			if(cnt > 1) {
				ok = 0;
				break;
			}
		}
		if(ok) return ;
	} while(next_permutation(all(ans)));
	ans.clear();
}

int main() {
	/*
	bool ok = 1;
	rep(i, 0, n) rep(j, i + 1, n) {
		int cnt = 0;
		rep(k, 0, n) cnt += (s[i][k] != s[j][k]);
		if(cnt < 3) ok = 0;
		cnt = 0;
		rep(k, 0, n) cnt += (s[k][i] != s[k][j]);
		if(cnt < 3) ok = 0;
	}
	de(ok);
	*/
	rep(i, 0, n) printf("%s\n", s[i]);
	fflush(stdout);
	char str[11];
	while(~scanf("%s", str)) {
		if(str[0] == 'R') {
			rep(i, 0, n) scanf("%s", t[i]);
			ans[0].clear(); ans[1].clear();
			solve1(ans[0]);
			solve2(ans[1]);
			if(sz(ans[0]) && sz(ans[1])) {
				printf("0\n");
				rep(i, 0, n) printf("%d%c", ans[0][i] + 1, " \n"[i == n - 1]);
				rep(i, 0, n) printf("%d%c", ans[1][i] + 1, " \n"[i == n - 1]);
			} else if(sz(ans[0])) {
				printf("1\n");
				rep(i, 0, n) printf("%d%c", ans[0][i] + 1, " \n"[i == n - 1]);
			} else if(sz(ans[1])) {
				printf("2\n");
				rep(i, 0, n) printf("%d%c", ans[1][i] + 1, " \n"[i == n - 1]);
			} else {
				assert(0);
			}
		} else {
			break;
		}
		fflush(stdout);
	}
	return 0;
}
