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
#define all(a) (a).begin(), (a).end()
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

const int N = 1e7 + 3e6;
const int M = 2e6 + 6;
int low[N], pp, S, m, n, l, r, ans;
ll sum;
vi tmp;
bitset<N> isp;
int cntp, p[M];
 
void getprime(int N) {
	cntp = 2;p[0] = 2;p[1] = 3;low[1] = pw(30);
	for (int i = 5, k = 1; i <= N; (k & 1) == 1 ? i+=2 : i+=4 , k++){
		if (!isp[k]) p[cntp++]=i, low[i] = i;
		for (int j = 2; j < cntp && p[j] * i <= N; j++) {
			low[p[j] * i] = p[j];
			isp[p[j] * i / 3] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

ll check(int mid) {
	ll res = mid / pp;
	rep(i, 1, S+1) {
		int x = mid / pp;
		rep(j, 0, m) if (pw(j) & i) x /= tmp[j];
		if (__builtin_popcount(i) & 1) res -= x;else res += x; 
	}
	return res;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> pp;
	if (pp > 80) {
		m = 1e9 / pp;
		getprime(m);
		//de(low[97]);
		rep(i, 1, m+1) if (low[i] >= pp) {
			n--;
			if (!n) {cout << i * pp; return 0;}
		}  
		cout << 0; return 0;
	}else {
		getprime(pp);
		rep(i, 0, cntp) if (p[i] < pp) tmp.pb(p[i]);
		m = sz(tmp);
		S = pw(m) - 1;
		l = pp; r = 1e9; ans = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			sum = check(mid);
			if (sum >= n) {
				ans = mid;
				r = mid - 1;
			}else l = mid + 1;
		}
		if (ans != -1) cout << ans;else cout << 0;
	}
	return 0;
}


