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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 +7;
int cnt, x, f[N], s[N];
db ans;

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(3);
	srand(time(0));
	rep(tim, 0, 100000) {
		cnt = 0;
		rep(i, 1, 1000) {
			x = rand() % 100;
			if (x >= 75) cnt++;
			if (cnt == 3) {f[i]++;break;}
		}
	}
	rep(i, 1, 1000) s[i] += s[i-1] + f[i], ans += i * (1.0 * f[i] / 100000); 
	de(ans);
	rep(i, 1, 1000) dd(i), de(1.0 * s[i] / 100000 * 100);
	
	return 0;
}


