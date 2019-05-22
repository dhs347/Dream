// n个物品放入m个包里，最少要几个包，考虑状态之间的有序性，逐个插入物品 
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

const int N = 200; 
int n, m, a[N], pos[1 << 24], b[N], S, f[1 << 24], l[1 << 24], x, y;

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 0, n) cin >> a[i];
	rep(i, 0, n) pos[pw(i)] = i;
	rep(i, 1, m+1) cin >> b[i];
	S = pw(n);
	sort(b+1, b+m+1);
	reverse(b+1, b+m+1);
	rep(i, 0, S) f[i] = 100000;
	f[S-1] = 0;
	l[S-1] = 0;
	per(i, 0, S) {
		x = i;if (f[x] == 100000) continue;
		while (x) {
			y = x & (-x);
			x -= y;
			int &t1 = f[i ^ y], &t2 = l[i ^ y];
			y = a[pos[y]];
			if (y <= l[i]) {
				if (t1 > f[i]) {
					t1 = f[i];
					t2 = l[i] - y;
				}else if (t1 == f[i]) t2 = max(t2, l[i] - y);
			}else {
				if (f[i] < m && b[f[i]+1] >= y) {
					if (t1 > f[i] + 1) {
						t1 = f[i] + 1;
						t2 = b[f[i]+1] - y;
					}else if (t1 == f[i] + 1) t2 = max(t2, b[f[i]+1] - y);
				} 
			}
		}
	}
	if (f[0] == 100000) cout << "NIE"; else cout << f[0];
	return 0;
}

