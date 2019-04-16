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

const int N = 3e5 + 10;
const db eps = 1e-17;
db ans, cnt;
string s;
int n, ne[N];
int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(4);
	cin >> n >> s;
	ne[n] = n;
	per(i, 0, n) if (s[i] == 'x' || s[i] == '?') ne[i] = i;else ne[i] = ne[i+1];
	rep(i, 0, n) if (s[i] != 'x') {
		cnt = 1;
		int j = i;
		if (s[i] == 'o') ans += 1;
		if (s[i] == '?') ans += 0.5, cnt /= 2;
		while (1) {
			int t = s[j] == 'o' ? ne[j] : ne[j+1];
			if (t < n && s[t] != 'x') {
				if (s[t] == '?') ans += (t - j - 1) * cnt * 2, cnt /= 2, ans += cnt * 2;
			} else {
				ans += (t - j - 1) * cnt * 2;
				break;
			}
			j = t;
			if (cnt < eps) break;
		}
	} 
	cout << ans << endl;
	return 0;
}

