#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << " "
#define dd(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 1e5 + 8, P = 1e9 + 7;
int n, ok[N], p[N];
ll a[N], ans;

struct Base{
	ll a[63], m;
	Base() {m = 0;memset(a, 0, sizeof(a));}
	bool ins(ll x) {
		for (int i = 62; ~i; --i) {
			if (x >> i & 1) {
				if (a[i]) x ^= a[i];
				else {
					m++;
					a[i] = x;return 1;
				}
			}
		}
		return 0;
	}
} B2[N];


int mul(int a, int b) {return 1ll * a * b % P;}

int add(int a, int b) {return (a + b) % P;}
 
int main() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	p[0] = 1;
	rep(i, 1, N) p[i] = mul(p[i-1], 2);
	while (cin >> n) {
		ans = 0;
		rep(i, 1, n+1) cin >> a[i];
		Base s, s2;
		B2[n+1] = s;
		per(i, 1, n+1) {
			B2[i] = B2[i+1];
			B2[i].ins(a[i]);
		}
		rep(i, 1, n+1) ok[i] = s.ins(a[i]);	
		rep(i, 1, n+1) {
			if (!ok[i]) ans = add(ans, p[n - 1 - s.m]);
			else {
				Base t = s2;
				rep(j, 0, 63) t.ins(B2[i+1].a[j]);
				if (!t.ins(a[i])) ans = add(ans, p[n - 1 - t.m]);
			}
			s2.ins(a[i]);
		}
		cout << ans << endl;
	}
	return 0;
}
