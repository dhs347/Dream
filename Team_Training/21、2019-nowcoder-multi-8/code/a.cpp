#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 3030;

int n, m, a[N][N], b[N][N], sta[N], top, val[N];
char s[N][N];
int L;

#define bac sta[top]

bool cmp(int i, int j) {
	return b[L][i] < b[L][j];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> (s[i] + 1);
	rep(i, 1, n + 1) rep(j, 1, m + 1) a[i][j] = s[i][j] - '0';
	ll ans = 0;
	rep(i, 1, n + 1) {
		L = i;
		rep(j, 1, m + 1) b[i][j] = (a[i][j] ? b[i - 1][j] + 1 : 0);
		top = 0;
		int z = 0;
		rep(j, 1, m + 1) {
			while(top && b[i][bac] >= b[i][j]) --top;
			sta[++top] = j, val[top] = sta[top - 1] + 1;
			if(a[i + 1][j] == 0) z = j;
			int r = upper_bound(val + 1, val + 1 + top, z) - val - 1;
			//int r = upper_bound(sta + 1, sta + 1 + top, z) - sta - 1;
			int l = upper_bound(sta + 1, sta + 1 + top, j + 1, cmp) - sta;
			if(1 <= l && l <= r && r <= top) ans += r - l + 1;
			//if(l <= r) ans += r - l + 1;
		}
	}
	cout << ans << endl;
	return 0;
}
