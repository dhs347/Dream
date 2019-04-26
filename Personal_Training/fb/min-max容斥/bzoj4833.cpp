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
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//const int P = 1e9 + 7;

//----

const int N = 1e6 + 5;
int a[N], n, T, P;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> P;
		a[1] = 1;
		int ans = 0;
		rep(i, 2, n+1) a[i] = add(mul(a[i-1], 2), a[i-2]);
		
		rep(i, 1, n+1) {
			int inv = kpow(a[i], P - 2);
			for (int j = i + i; j <= n; j += i) a[j] = mul(a[j], inv);
			if (i > 1) a[i] = mul(a[i], a[i-1]);
			ans = add(ans, mul(a[i], i));
		}
		cout << ans << endl;
	}
	return 0;
}


