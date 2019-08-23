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
#define pw(c) (1ll<<(c))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 505, M = 26;

int cnt[26], len[26], totlen;
vector<pii> vec;
char str[N], s[26][N];

void print(char s[]) {
	printf("? %s\n", s);
	fflush(stdout);
	totlen += strlen(s);
	assert(totlen <= 6e5);
}

void gao(int c, int &res) {
	int l = 1, r = 500; res = 0;
	while(l <= r) {
		int mid = l + r >> 1;
		rep(i, 0, mid) str[i] = c + 'a'; str[mid] = '\0';
		print(str);
		scanf("%s", str);
		if(str[0] == 'Y') {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
}

int main() {
	rep(i, 0, M) {
		gao(i, cnt[i]);
		vec.pb(mp(cnt[i], i));
	}
	sort(all(vec));
	len[0] = vec[0].fi;
	rep(i, 1, M) len[i] = len[i - 1] + vec[i].fi;
	rep(i, 0, len[0]) s[0][i] = vec[0].se + 'a';
	rep(i, 1, M) {
		int c = vec[i].se;
		int pos = 0, tot = vec[i].fi;
		rep(j, 0, len[i - 1]) {
			char x = j ? s[i - 1][j - 1] : ' ';
			char y = s[i - 1][j];
			if(tot) {
				int t = 1;
				while(1) {
					int p = 0;
					rep(k, 0, j) if(s[i - 1][k] == x || s[i - 1][k] == y) str[p++] = s[i - 1][k];
					rep(k, 0, t) str[p++] = c + 'a';
					rep(k, j, len[i - 1]) if(s[i - 1][k] == x || s[i - 1][k] == y) str[p++] = s[i - 1][k];
					str[p] = '\0';
					print(str);
					scanf("%s", str);
					if(str[0] == 'Y') {
						++t;
					} else {
						t--;
						break;
					}
				}
				rep(k, 0, t) s[i][pos++] = c + 'a';
				tot -= t;
			}
			s[i][pos++] = s[i - 1][j];
		}
		while(pos < len[i]) s[i][pos++] = c + 'a';
	}
	s[M - 1][len[M - 1]] = '\0';
	printf("! %s\n", s[M - 1]);
	fflush(stdout);
	return 0;
}
