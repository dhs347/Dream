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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int P = 998244353;
const int N = 1e5 + 5;
int T;
ll a[N], c[N], b[N], m;

const int B = N / 2000;

unordered_map<int, int> M;

int phi(int n) {
	if (M.count(n)) return M[n];
	int r = n, nn = n;
	for (int i = 2; i * i  <= n; i ++) if (n % i == 0) {
		r = r / i * (i - 1);
		while (n % i == 0) n /= i;
	}
	if (n > 1) r = r / n * (n - 1);
	return M[nn] = r;
}

int kpow(int a, ll b) {
	b %= (P - 1);
	int r = 1;
	while (b) {
		if (b & 1) r = 1ll * r * a % P;
		a = 1ll * a * a % P;
		b >>= 1;
	}
	return r;
}

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	int n = 1e5;
	rep(i, 1, n+1) a[i] = phi(i);
	//sort(a+1, a+n+1);
	//int m = unique(a+1, a+n+1) - a;
	//cout << m << endl;
	int s = 0;
	rep(i, 1, n+1) {
		int t = 0;
		rep(j, 1, i) {
				t = t + 1ll * a[i] * a[j] % P * kpow(2, a[i] * a[j]) % P;
				if (t >= P) t-= P;
		}
		//de(i);
		s = (s + t) % P;
		if ()
		if (i % B == 0) b[++m] = s, c[m] = i;
	}
	de(m);
	rep(i, 1, m+1) cout << b[i] << ",";
	return 0;
}
