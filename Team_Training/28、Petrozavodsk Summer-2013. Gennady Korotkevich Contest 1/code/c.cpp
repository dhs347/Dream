#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;


#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

const int N = 101010, P = 1e9 + 7;

int n, m, cnt[10], ans;
int h[6][N], c[N], jc[N], in[N], tmp[2][N], lim[100];
char s[N];

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int C(int m, int n) {
	if(m > n) return 0;
	if(m < 0) return 0;
	int ans = mul(jc[n], mul(in[m], in[n - m]));
//	if(ans) de(ans);
	return ans;
}

int calc(int x, int y, int o = 0, int l1 = 0, int l2 = 0) {
	//dd(x), de(y);
	if(x % 2 != 0) return 0; 
	if(o) {
		//
		x = x / 2 - l1; if(x < 0) x = 0; 
		int ans = 0;
		for(int k = 0; x + k <= y; ++k) {
			if (y - x - k - l1 - l2 >= 0) ans = add(ans, C(x + k + l1, y));
		}
		return ans;
	} else {
		x =  x / 2 - l1;
		if(x < 0 || y - x - l1 - l2 < 0) return 0;
		return C(x + l1, y);
	}
}

int solve() {
	rep(i, 0, 5) {
		int j = 9 - i;
		c[i] = cnt[j] - cnt[i];
		rep(d, 0, m + 1) h[i][d] = mul(calc(c[i] + d, d, i == 0, lim[i], lim[j]), in[d]);//, dd(i), dd(d), de(h[i][d]);
	}
	int o = 1;
	//debug_arr(c,4);
	//debug_arr(h[0],m);
	rep(i, 0, m + 1) tmp[0][i] = h[0][i];
	rep(t, 1, 5) {
		fill_n(tmp[o], m + 1, 0);
		rep(s, 0, m + 1) {
			rep(i, 0, s + 1) {
				int j = s - i;
				tmp[o][s] = add(tmp[o][s], mul(tmp[o ^ 1][i], h[t][j]));
			}
		}
		o ^= 1;
	}
	int ans = mul(tmp[o ^ 1][m], jc[m]);
	return ans;
}

int main() {
	freopen("can.in", "r", stdin);
	freopen("can.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> (s + 1);
	n = strlen(s + 1);
	m = 0;
	rep(i, 1, n + 1) {
		if(s[i] == '?') {
			m++;
		} else {
			cnt[s[i] - '0']++;
		}
	}
	jc[0] = 1; rep(i, 1, N) jc[i] = mul(jc[i - 1], i);
	in[N - 1] = kpow(jc[N - 1], P - 2);
	per(i, 0, N - 1) in[i] = mul(in[i + 1], i + 1);
	rep(i, 1, 6) {
		int j = 10 - i;
		--cnt[i], --cnt[j];
		if (cnt[i] < 0) lim[i] = abs(cnt[i]);
		if (cnt[j] < 0) lim[j] = abs(cnt[j]);
		ans = add(ans, solve());
		//dd(i), dd(j), de(ans); 
		++cnt[i], ++cnt[j];
		lim[i] = lim[j] = 0;
	}
	cout << ans << endl;
	return 0;
}

