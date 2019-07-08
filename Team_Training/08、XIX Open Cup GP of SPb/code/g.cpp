#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) -1; i >= (a); --i)
#define endl "\n"
#define pw(a) (1ll << (a))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef __int128 ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int n, d;
int cnt[10];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> d;
	if(d == 9) {
		++cnt[n % 8];
		cnt[8] += n / 8;
	} else {
		++cnt[n % 9];
		cnt[9] += n / 9;
		int x = n % 9;
		if(n % 9 && n % 9 == d) {
			if(n / 9) {
				if(d == 8) {
					if(x + 2 < 10) {
						--cnt[x];
						++cnt[x + 2];
						--cnt[9];
						++cnt[7];
					} else {
						--cnt[x];
						++cnt[1];
						++cnt[x - 1];
					}
				} else {
					--cnt[n % 9];
					++cnt[n % 9 + 1];
					--cnt[9];
					++cnt[8];
				}
			} else {
				--cnt[x];
				++cnt[1];
				++cnt[x - 1];
			}
		}
	}
	rep(i, 1, 10) {
		rep(j, 0, cnt[i]) cout << i;
	}
	cout << endl;
	//
	return 0;
}
