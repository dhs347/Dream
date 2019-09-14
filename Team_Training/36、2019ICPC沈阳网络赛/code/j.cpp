#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
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

const int P = 1e9 + 7;
const int N = 1e6 + 7;
int n, m, T, jc[N], inv[N], ans, x;

int add(int a, int b) {
		if((a += b) >= P) a -= P;
		return a < 0 ? a + P : a;
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


int C(int n, int m) {
	if (m < 0 || m > n) return 0;
	return mul(jc[n], mul(inv[m], inv[n - m]));
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	n = 1e6 + 1;
	jc[0] = 1; rep(i, 1, n+1) jc[i] = mul(jc[i-1], i);
	inv[n] = kpow(jc[n], P - 2);
	per(i, 0, n) inv[i] = mul(inv[i+1], i+1);
	rep(cas, 0, T) {
		cin >> n >> x;
		ans = jc[n];
		rep(i, x+1, n+1) ans = add(ans, -mul(C(n, i), mul(jc[i - 1], jc[n - i])));
		cout << mul(ans, inv[n]) << endl;
	}
	return 0;
}
