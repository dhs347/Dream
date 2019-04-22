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

const int N = 400;
db f[N][2], t, ans;
int n, m;

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(5);
	cin >> n >> m;
	f[1][1] = 1;
	f[2][0] = 1.0 * (m - 1) / m;
	rep(i, 3, n+1) { 
		t = 1;
		per(j, 1, i) {
			f[i][0] += f[j][0] * t * (m - 2) / m * (i - j) + f[j][1] * t * (m - 1) / m * (i - j);
			f[i][1] += f[j][0] * t * 1 / m * (i - j);
			t /= m;
		}
	}
	t = 1;
	rep(i, 1, n+1) {
		db tmp = f[n - i + 1][0] * i * t * i;
		ans += tmp;
		t /= m;
	}
	ans += t * n * m;
	cout << ans << endl;
	return 0;
}

