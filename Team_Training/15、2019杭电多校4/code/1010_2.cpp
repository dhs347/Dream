
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

ll mulmod(ll a, ll b, ll p) {
	__int128 t = a;
	return t * b % p;
}

ll powmod(ll a, ll b, ll p) {
	a %= p;
	ll r = 1;
	while(b) {
		if(b & 1) r = mulmod(r, a, p);
		a = mulmod(a, a, p);
		b >>= 1;
	}
	return r;
}
int spp(ll n, int base) 
{
	ll n2 = n - 1, res;
	int s = 0;
	while(n2 % 2 == 0) n2 >>= 1, s++;
	res = powmod(base, n2, n);
	if((res == 1) || (res == n - 1)) return 1;
	s--;
	while(s >= 0) {
		res = mulmod(res, res, n);
		if(res == n - 1) return 1;
		s--;
	}
	return 0;
}
int isp(ll n) {
	static ll testNum[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	static ll lim[] = {4, 0, 1373653ll, 25326001ll, 25000000000ll, 2152302898747ll, 3474749660383ll, 341550071728321ll, 0, 0, 0, 0};
	if(n < 2 || n == 3215031751ll) return 0;
	for(int i = 0; i < 12; ++i) {
		if(n < lim[i]) return 1;
		if(spp(n, testNum[i]) == 0) return 0;
	}
	return 1;
}
int ansn; ll ans[1000];
ll func(ll x, ll n) {
	return (mulmod(x, x, n) + 1) % n;
}
ll pd(ll n) {
	ll i, x, y, p;
	if(isp(n)) return n;
	if(!(n & 1)) return 2;
	for(i = 1; i < 20; ++i) {
		x = i; y = func(x, n); p = __gcd((y - x + n) % n, n) % n;
		while(p == 1) {
			x = func(x, n); y = func(func(y, n), n); p = __gcd((y - x + n) % n, n) % n;
		}
		if(p == 0 || p == n) continue;
		return p;
	}
	assert(0);
}
void factor(ll n) {
	ll x;
	x = pd(n);
	if(x == n) {
		ans[ansn++] = x; return ;
	}
	factor(x), factor(n / x);
}

int T;
ll n;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	//ll p = 1ll * 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29 * 31 * 37 * 41 * 43; 
	//de(p);
	T =  50000;
	ll p = 1ll * 2 * 3 * 5 * 7 * 11;
	rep(cas, 0, T) {
		ansn = 0;
		//cin >> n;
		//n = 1000000000000000000ll;
		n = p;	
		factor(n);
		
		sort(ans, ans+ansn);
		int cnt = 1, an = 100;
		rep(i, 1, ansn) {
			if (ans[i] != ans[i-1]) an = min(an, cnt), cnt = 1;else cnt++;
		}
		an = min(an, cnt);
		cout << an << endl;
	}
	return 0;
}
