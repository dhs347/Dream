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

const int N = 1e6 + 7, P = 1e9 + 7;

int n, a[N], s[N], v[N], s2[N];

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int sub(int a, int b) {
	if((a -= b) < 0) a += P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	int pre = 1;
	a[0] = 1; rep(i, 1, n + 1) {
		a[i] = mul(mul(pre, 2), kpow(i, P - 2)); // todo
		pre = add(pre, a[i]);
		dd(i), de(a[i]);
	}
	rep(i, 0, n + 1) s2[i] = mul(a[i], a[i]);
	rep(i, 1, n + 1) s2[i] = add(s2[i], s2[i - 1]);
	s[0] = 1; rep(i, 1, n + 1) s[i] = add(s[i - 1], a[i]);
	pre = 1;
	v[0] = 1; rep(i, 1, n + 1) {
		int k1 = kpow(i, P - 2);
		int k2 = mul(k1, k1);
		int t = add(k1, k2); t = mul(t, 2);
		v[i] = mul(pre, t);
		t = sub(mul(s[i - 1], s[i - 1]), s2[i - 1]);
		t = mul(t, k2);
		v[i] = add(v[i], t);
		pre = add(pre, v[i]);
	}
	int ans = sub(v[n], mul(a[n], a[n]));
	cout << ans << endl;
	return 0;
}
