#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010, M = 2;

int n, k, L[M], R[M], cnt[N][M], pre[M], ne[N][M], now;
string s;

inline bool check(int i, int j) {
	int p = ne[now][j];
	if(p >= n) return 0;
	rep(t, 0, M) if(cnt[p + 1][t] < max(0, L[t])) return 0;
	int tot = 0;
	rep(t, 0, M) tot += min(cnt[p + 1][t], R[t]);
	return k - i <= tot;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> s >> k) {
		n = sz(s);
		rep(i, 0, M) cin >> L[i] >> R[i];
		rep(i, 0, M) cnt[n][i] = 0;
		per(i, 0, n) rep(j, 0, M) cnt[i][j] = cnt[i + 1][j] + (s[i] - 'a' == j), dd(i), dd(j), de(cnt[i][j]);
		int tot = 0;
		rep(i, 0, M) tot += min(R[i], cnt[0][i]);
		bool ok = (k <= tot);
		rep(i, 0, M) if(cnt[0][i] < L[i]) {
			ok = 0;
			break;
		}
		if(!ok) {
			cout << -1 << endl;
			continue;
		}
		rep(i, 0, M) pre[i] = n;
		per(i, 0, n) {
			pre[s[i] - 'a'] = i;
			rep(j, 0, M) ne[i][j] = pre[j], dd(i), dd(j), de(pre[j]);
		}
		now = 0;
		rep(i, 1, k + 1) {
			rep(j, 0, M) dd(i), dd(j), dd(L[j]), de(R[j]);
			rep(j, 0, M) {
				--L[j], --R[j];
				if(check(i, j)) {
					cout << (char)(j + 'a') << endl;
					break;
				}
				++L[j], ++R[j];
			}
		}
		cout << endl;
	}
	return 0;
}
