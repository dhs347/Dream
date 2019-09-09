#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010, M = 30;

int n, a[2][N], ne[2][N * M][2], cnt[2][N * M], L[2];
vi ans;

void init(int ne[][2], int cnt[], int &L) {
	rep(i, 0, L + 1) fill_n(ne[i], 2, 0), cnt[i] = 0; L = 0;
}

void gao(int a[], int ne[][2], int cnt[], int &L) {
	init(ne, cnt, L);
	rep(i, 1, n + 1) {
	//	de(i);
		cin >> a[i];
		int p = 0; per(j, 0, M) {
			int c = (a[i] >> j & 1);
			if(!ne[p][c]) ne[p][c] = ++L;
			p = ne[p][c]; ++cnt[p]; //de(p);
		} 
	}
	//rep(i, 0, L + 1) dd(i), de(cnt[i]);
}

int work() {
	int ans = 0, p = 0, q = 0;
	rep(i, 0, M) {
		int t = -1;
		rep(o, 0, 2) if(cnt[0][ne[0][p][o]] && cnt[1][ne[1][q][o]]) {
			--cnt[0][ne[0][p][o]], --cnt[1][ne[1][q][o]];
			t = 0; p = ne[0][p][o], q = ne[1][q][o];
		//	dd(i), dd(o), de(o);
			break;
		}
		if(t == -1) rep(o, 0, 2) if(cnt[0][ne[0][p][o]] && cnt[1][ne[1][q][o ^ 1]]) {
			--cnt[0][ne[0][p][o]], --cnt[1][ne[1][q][o ^ 1]];
			t = 1; p = ne[0][p][o], q = ne[1][q][o ^ 1];
		//	dd(i), dd(o), de((o ^ 1));
			break;
		}
		ans = ans << 1 | t;
	}
	return ans; 
}

void solve() {
	cin >> n;
	rep(o, 0, 2) gao(a[o], ne[o], cnt[o], L[o]);
	ans.clear();
	rep(i, 1, n + 1) ans.pb(work());
	sort(all(ans));
	rep(i, 0, n) cout << ans[i] << " \n"[i == n - 1];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve(); 
	return 0;
}

