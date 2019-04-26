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
typedef long double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 55;
int T, n, len, S, d;
db f[N][2][N * N / 2], ans;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(15);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		f[0][0][0] = 1;
		rep(i, 1, n+2) {
			rep(j, 0, (i + 1) * i / 2 + 1) f[i][0][j] = f[i][1][j] = 0;
			rep(j, 0, i) {
				len = i - j - 1;
				d = (len + 1) * len / 2; 
				rep(k, 0, j * (j + 1) / 2 + 1) {
					f[i][0][k + d] += f[j][1][k];
					f[i][1][k + d] += f[j][0][k];
				}
			}
		}
		ans = 0;
		int cnt = 0;
		S = n * (n + 1) / 2;
		rep(i, 0, S) {
			ans -= f[n+1][1][i] * S / (S - i);
			ans += f[n+1][0][i] * S / (S - i);
		} 
		cout << ans << endl;
	}
	return 0;
}


