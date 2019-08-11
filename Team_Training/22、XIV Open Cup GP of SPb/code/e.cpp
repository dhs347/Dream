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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 7;
ll ans;
int cntp, p[N],  isp[N], f[N], n;

int main() {
//	freopen("fourprimes.in", "r", stdin);
//	freopen("fourprimes.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 2, n+1) {
		if (!isp[i]) {
			p[++cntp] = i;
			for (int j = i + i; j <= n; j += i) isp[j] = 1;
		}
	}
	rep(i, 1, cntp+1) rep(j, 1, cntp+1) {
		if (p[i] + p[j] > n) break;
		f[p[i] + p[j]]++;
	}
	rep(i, 1, n+1) ans += 1ll * f[i] * f[n - i];
	cout << ans << endl;
	return 0;
}
