#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1010;

string s;
int t[N], dp[N];
bool check(int l, int r) {
	rep(i, l, r) if(t[i]) return 0;
	return 1;
}
char calc(int s) {
	if(s < 10) return '0' + s;
	return s - 10 + 'a';
}
void solve() {
	cin >> s;
	rep(i, 0, 32) {
		int &c = t[i] = 0;
		rep(j, i * 4, i * 4 + 4) c = c * 2 + s[j] - '0';
	}
	int ans = 0, pans = -1; dp[0] = check(0, 4);
	rep(i, 1, 8) {
		dp[i] = (check(i * 4, i * 4 + 4) ? dp[i - 1] + 1 : 0);
		if(dp[i] >= dp[ans]) pans = ans, ans = i;
	}
	if(dp[ans] > 1) {
		int l = ans - dp[ans] + 1, r = ans;
//		dd(l), de(r);
		if(r == 7 && pans >= 0 && dp[ans] == dp[pans]) {
			int nl = pans - dp[pans] + 1, nr = pans;
			if(nl) l = nl, r = nr;
		}
	//	dd(l), de(r);
		rep(i, 0, 8) {
			if(l <= i && i <= r) {
				if(i == l) cout << ':';
				if(i == 0) cout << ':';
				continue;
			}
			int F = 0;
			rep(j, i * 4, i * 4 + 4) {
				auto u = calc(t[j]);
				if(u == '0') {
					if(F) {
						cout << u;
					} 
				} else {
					cout << u; F = 1;
				}
			}
			if(!F) cout << '0';
			if(i != 7) cout << ":";
		}
		cout << endl;
	} else {
		rep(i, 0, 8) {
			int F = 0;
			rep(j, i * 4, i * 4 + 4) {
				auto u = calc(t[j]);
				if(u == '0') {
					if(F) {
						cout << u;
					} 
				} else {
					cout << u; F = 1;
				}
			}
			if(!F) cout << '0';
			cout << ":\n"[i == 7];
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int ca = 0;
	//de(int(':'));
	//de(int('0'));
	int T; cin >> T; while(T--) {
		cout << "Case #" << ++ca << ": ";
		solve();
	}
	return 0;
}
