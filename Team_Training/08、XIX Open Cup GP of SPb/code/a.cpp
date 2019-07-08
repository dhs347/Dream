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
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const ll P = pw(31), salt = 1748665573;

ll add(ll a, ll b) {
	return (a + b) % P;
}

ll mul(ll a, ll b) {
	return a * b % P;
}

struct mat{
	ll a[2][2];
	mat() {memset(a, 0, sizeof(a));}
	mat operator * (const mat &c) const {
		mat r;
		rep(i, 0, 2) rep(j, 0, 2) rep(k, 0, 2) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
		return r;
	}
} c[8];

/*int ok;
int a[] = {1, 3, 2, 3, 0, 0, 4, 2};
int b[] = {484, 467, 469, 363, 621, 504, 291, 503};
*/

ll seed, now, wait, ans1[10], ans2[10], a[10], b[10], tim, sum, ma;
string s;

ll h(string s) {
	ll r = 0;
	rep(i, 0, sz(s)) r = (r * 31 + s[i]) % P;
	return r;
}

ll ran() {
	seed = seed * 1234567893 + 151515151;
	seed %= P;
	return seed;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cout << setiosflags(ios ::fixed);
	cout << setprecision(10);
	cin >> now >> wait >> s;
	ll ha = h(s);
	//de((salt ^ now ^ ha));
	rep(i, now, now + wait + 1) {
		seed = salt ^ i ^ ha;
		sum = 0;
		rep(j, 0, 8) {
			b[j] = 500;
			rep(t, 0, 10000) b[j] += ran() % 3 - 1;
			//cout << b[j] << " \n"[j == 7];
			sum += abs(500 - b[j]);
		}
		rep(j, 0, 8) {
			a[j] = ran() % 5;
			//cout << a[j] << " \n"[j == 7];
		}
		if (sum > ma) {
			ma = sum; tim = i;
			rep(j, 0, 8) ans1[j] = b[j], ans2[j] = a[j];
		}
	}
	cout << tim << " " << 1.0 * ma / 8 << endl;
	rep(j, 0, 8) cout << ans1[j] << " \n"[j == 7];
	rep(j, 0, 8) cout << ans2[j] << " \n"[j == 7];
/*	return 0;
	mat r;
	r.a[0][0] = 1234567893;
	r.a[0][1] = 151515151;
	r.a[1][0] = 0;
	r.a[1][1] = 1;
	c[0] = r;
	ll n = 80000;
	rep(i, 1, n+1) c[0] = c[0] * r;
	rep(i, 1, 8) c[i] = c[i-1] * r;
	n = pw(31);
	for (ll seed = 0; seed < n; seed++) {
		ok = 1;
		rep(j, 0, 8) {
			if (add(mul(seed, c[j].a[0][0]), c[j].a[0][1]) % 5 != a[j]) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			ok = 1;
			mat cc = r;
			rep(j, 0, 8) {
				int t = 500;
				rep(p, 0, 10000) {
						t += add(mul(seed, cc.a[0][0]), cc.a[0][1]) % 3 - 1;
						cc = cc * r;
				}
				//dd(t), de(b[j]);
				if (t != b[j]) {
					ok = 0;
					break;
				}
			}
			if (ok) de(seed);
		}
	}*/
	return 0;
}
