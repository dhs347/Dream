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
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e4 + 10;
string s;
int n, a[N];
db b[N], k[N], p[N], f[N], ans;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(1);
	cin >> s;
	n = sz(s);
	rep(i, 0, n) a[s[i] - 'A']++;
	rep(i, 0, n+1) p[i] = 1.0 * i / n;
	b[1] = n / 2.0; k[1] = 1;
	rep(i, 2, n) {
		db t = 1 - (i - 1) / 2.0 / i * k[i-1];
		b[i] = 1 / (2.0 * i * (n - i) / n / (n - 1)) + (i - 1) / 2.0 / i * b[i-1];
		b[i] /= t; k[i] = (i + 1) / 2.0 / i / t;
	} 
	per(i, 1, n) f[i] = k[i] * f[i+1] + b[i];
	rep(i, 0, 26) ans += p[a[i]] * f[a[i]];
	cout << ans << endl; 
	return 0;
}

