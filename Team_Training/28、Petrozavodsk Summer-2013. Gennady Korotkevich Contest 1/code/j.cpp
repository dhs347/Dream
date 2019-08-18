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

ll n, ans;

const int N = 3e6 + 10;
bool f[N];
int p[N], cntp;

int cal(ll n) {
	int r = 1;
	if (n == 0) return 0;
	rep(i, 1, cntp+1) {
		if (p[i] > n) break;
		if(n % p[i] == 0){
			int cnt = 1; n /= p[i];
			while (n % p[i] == 0) {
				n /= p[i]; cnt++;
			}
			r *= (cnt + 1);
		}
	}
	if (n > 1) r = r * 2;
	return r - 1;
}

int main() {
	freopen("job.in", "r", stdin);
	freopen("job.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	//n = 1ll * 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29 * 31;
	//de(n);
	

	ll m = sqrt(n);
	//int ans2 = 0;
	//rep(i, 1, n+1) if (n % i == 0 || i % (n % i) == 0) ans2++;
	//de(ans2);
	rep(i, 2, m+1) {
		if (!f[i]) {
			p[++cntp] = i;
			for (int j = i + i; j <= m; j += i) f[j] = 1;
		}
	}
	rep(i, 1, m+1) if (n % i == 0) {
		ans += cal(i - 1) + 1;
		if (1ll * i * i != n) ans += cal(n / i - 1) + 1;
	}
	cout << ans << endl;
	return 0;
}
