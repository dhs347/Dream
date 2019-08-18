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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e6 + 6;

int n, cnt[11], now[11], ans[N], tmp[N], pos, m;
char s[N];

int calc() {
	while(!now[pos]) ++pos;
	--now[pos];
	return pos;
}

void gao(int a[]) {
	rep(i, 0, m) if(a[i] >= 10) a[i] -= 10, ++a[i + 1];
}

bool bg(int a[], int b[]) {
	per(i, 0, m + 1) if(a[i] != b[i]) return a[i] > b[i];
	return 0;
}
void upd(int a[], int b[]) {
	if(bg(a, b)) rep(i, 0, m + 1) a[i] = b[i];
}

void solve() {
	bool spe = 1;
	cin >> s; n = strlen(s); m = n >> 1;
	memset(cnt, 0, sizeof(cnt));
	rep(i, 0, n) ++cnt[s[i] - '0'];
	rep(i, 0, 5) if(cnt[i] != cnt[9 - i]) spe = 0;
	rep(i, 0, m + 1) ans[i] = 9;
	if(spe) {
		cout << 1 << endl;
		return ;
	}
	rep(i, 0, 10) if(cnt[i]) {
		--cnt[i];
		rep(j, i, 10) if(cnt[j]) {
			--cnt[j];
			rep(t, 0, 11) now[t] = cnt[t];
			int p = m; tmp[p--] = 0;
			rep(t, 0, 5) {
				int k = min(now[t], now[9 - t]);
				now[t] -= k, now[9 - t] -= k;
				while(k--) tmp[p--] = 9;
			}
			tmp[p--] = i + j; pos = 0;
			if(i + j >= 10) {
				per(i, 0, p + 1) tmp[i] = calc() + calc();
				gao(tmp); tmp[m] = 0;
			} else if(i + j < 9) {
				rep(i, 0, p + 1) tmp[i] = calc() + calc();
				gao(tmp);
				rep(i, 0, m) tmp[i] = 9 - tmp[i];
				++tmp[0]; gao(tmp);
			}
			upd(ans, tmp);
			++cnt[j];
		}
		++cnt[i];
	}
	n = m + 1;
	while(n > 1 && !ans[n - 1]) --n;
	per(i, 0, n) cout << ans[i]; cout << endl;
}

int main() {
	freopen("done.in", "r", stdin);
	freopen("done.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
