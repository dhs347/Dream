#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i++)
#define sz(a) (int)a.size()
#define dd(a) cout << #a << " = " << a << " "
#define de(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

typedef __int128 T;
const int N = 1e4 + 10;
ll read[N];
T a[N] , b[N];

void output(T x){
	if(x < 0) x = -x , cout << "-";
	if(x == 0) cout << 0;
	else {
		string s;
		while(x) s.pb('0'+(x%10)),x/=10;
		reverse(all(s));
		cout << s;
	}
}

int main() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	ll n , m;
	while(cin >> n >> m) {
		T down = n * m * n * m, up = 0;
		rep(i,0,n) cin >> read[i];
		rep(i,0,n) a[i] = read[i] * n;
		T sum = 0;
		rep(i,0,n) sum += a[i];
		T d = n * m - sum;
		T get = d / n;
		rep(i,0,n) b[i] = a[i] + get;
		up += get * get * n;
		vector<T> pos;
		T del = 0;
		rep(i,0,n) {
			if(b[i] < 0) {
				up += b[i] * b[i];
				del += -b[i];
			} else if(b[i] > 0) {
				pos.pb(b[i]);
			}
		}
		T multi = 1;
		sort(all(pos));
		T presum = 0 , backup = del;
		rep(i,0,sz(pos)) {
			if(del > 0) {
				T candel = pos[i] - presum;
				T total = candel * (sz(pos) - i);
				if(del >= total) {
					presum += candel;
					del -= total;
				} else {
					del = 0;
					multi = sz(pos) - i;
				}
			}
		}
		down *= multi * multi;
		up *= multi * multi;
		rep(i,0,sz(pos)) pos[i] *= multi;
		presum = 0;
		del = backup * multi;
		rep(i,0,sz(pos)) {
			if(del > 0) {
				T candel = pos[i] - presum;
				T total = candel * (sz(pos) - i);
				if(del >= total) {
					presum += candel;
					del -= total;
				} else {
					presum += del / (sz(pos) - i);
					del = 0;
				}
			}
			up += presum * presum;
		}
		T g = __gcd(up , down);
		up /= g;
		down /= g;
		if(down == 1) output(up);
		else {
			output(up);
			cout << "/";
			output(down);
		}
		cout << endl;
		//		cout << up << " " << down << endl;
	}
	return 0;
}
