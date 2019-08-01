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

const int N = 101010, M = 26;

int n, k, L[M], R[M], cnt[N][M], pre[M], ne[N][M], now;
string s;

bool check(int k, int p) {
	int sl = 0, sr = 0;
	rep(i, 0, M) {
		if(cnt[p][i] < L[i]) return 0;
		sl += max(0, L[i]);
		sr += min(R[i], cnt[p][i]);
	}
	return sl <= k && k <= sr;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> s >> k) {
		n = sz(s);
		rep(i, 0, M) cin >> L[i] >> R[i];
		rep(i, 0, M) cnt[n][i] = 0;
		per(i, 0, n) rep(j, 0, M) cnt[i][j] = cnt[i + 1][j] + (s[i] - 'a' == j);
		rep(i, 0, M) pre[i] = n;
		per(i, 0, n) {
			pre[s[i] - 'a'] = i;
			rep(j, 0, M) ne[i][j] = pre[j];
		}
		if(!check(k, 0)) {
			cout << -1 << endl;
			continue;
		}
		now = 0;
		rep(i, 1, k + 1) {
			rep(j, 0, M) {
				--L[j], --R[j];
				if(R[j] >= 0 && ne[now][j] < n && check(k - i, ne[now][j] + 1)) {
					cout << (char)(j + 'a');
					now = ne[now][j] + 1;
					break;
				}
				++L[j], ++R[j];
			}
		}
		cout << endl;
	}
	return 0;
}
