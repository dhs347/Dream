// 两堆数，每次可以合并两个，问最少几次可以两堆一样
// 转移分步的思想要注意，可以减少复杂度 
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
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 24, M = pw(20) + 7;
int n, m , S, t;
char f[M];
bool ok[M];
short s[M], a[N];
int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 0, n) cin >> a[i];
	cin >> m;
	rep(i, n, n+m) cin >> a[i], a[i] = -a[i];
	n = n + m;
	S = pw(n) - 1;
	rep(i, 0, S) {
		for (int x = i, t = x & -x; x; x -= t, t = x & -x){
			s[i] += a[__builtin_ctz(t)]; 
		}
		ok[i] = s[i] == 0;
	}
	rep(i, 0, S) {
		f[i] += ok[i];
		for (int x = ~i, t = x & -x; t <= S; x -= t, t = x & -x){
			f[t | i] = f[t | i] < f[i]  ? f[i] : f[t | i];
		}
	}
	cout << n - f[S] * 2;
	return 0;
}


