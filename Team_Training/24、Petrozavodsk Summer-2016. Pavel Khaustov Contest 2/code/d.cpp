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

const int N = 66;

int n, m, ans, now, pre[N], cntg;
pii a[N];
char s[N][N];
bool use[N], vis[N][N];

void dfs(int cnt) {
	if(cnt == 0) {
		ans = max(ans, now);
		return ;
	}

	rep(i, 0, n) rep(j, 0, m) if(!vis[i][j]) {
		vis[i][j] = 1;
		// (i, j) (i, j+1)
		if(!vis[i][j + 1]) {
			vis[i][j + 1] = 1;
			rep(k, 0, 28) if(!use[k]) {
				use[k] = 1;
				int pn = now, pg = cntg;
				if(s[i][j] == 'G') now += a[k].fi, --cntg;
				if(s[i][j + 1] == 'G') now += a[k].se, --cntg;
				dfs(cnt - 2);

				now = pn; cntg = pg;
				if(s[i][j] == 'G') now += a[k].se, --cntg;
				if(s[i][j + 1] == 'G') now += a[k].fi, --cntg;
				dfs(cnt - 2);

				now = pn; cntg = pg;
				use[k] = 0;
			}
			vis[i][j + 1] = 0;
		}
		// (i, j) (i+1, j)
		if(!vis[i + 1][j]) {
			vis[i + 1][j] = 1;
			rep(k, 0, 28) if(!use[k]) {
				use[k] = 1;
				int pn = now, pg = cntg;
				if(s[i][j] == 'G') now += a[k].fi, --cntg;
				if(s[i + 1][j] == 'G') now += a[k].se, --cntg;
				dfs(cnt - 2);

				now = pn; cntg = pg;
				if(s[i][j] == 'G') now += a[k].se, --cntg;
				if(s[i + 1][j] == 'G') now += a[k].fi, --cntg;
				dfs(cnt - 2);

				now = pn; cntg = pg;
				use[k] = 0;
			}
			vis[i + 1][j] = 0;
		}
		vis[i][j] = 0;
		return ;
	}
}

bool solve() {
	int cnt = 0; ans = cntg = 0;
	rep(i, 0, n) cin >> s[i];
	rep(i, 0, n) rep(j, 0, m) vis[i][j] = (s[i][j] == 'B'), cnt += (!vis[i][j]), cntg += (s[i][j] == 'G');
	rep(i, 0, n + 1) vis[i][m] = 1;
	rep(i, 0, m + 1) vis[n][i] = 1;
	rep(i, 0, 28) use[i] = 0;
	if(cnt & 1) return 0;
	now = 0;
	dfs(cnt);
	return 1;
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	int p = 0, cp = 0;
	rep(i, 0, 7) rep(j, i, 7) a[p++] = mp(i, j), pre[++cp] = i, pre[++cp] = j;
	sort(pre + 1, pre + cp + 1);
	reverse(pre + 1, pre + cp + 1);
	rep(i, 1, cp + 1) pre[i] += pre[i - 1];
	int ca = 0;
	while(cin >> n >> m) {
		if(!n && !m) break;
		cout << "Case " << ++ca << ": ";
		if(solve()) {
			cout << ans << endl;
		} else {
			cout << "No solution" << endl;
		}
	}
	return 0;
}
