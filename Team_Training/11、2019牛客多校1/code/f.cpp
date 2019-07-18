#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i++)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << " "
#define dd(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

typedef ll T;
struct P {
	T x , y;
	P(){}
	P(T x,T y):x(x),y(y){}
	P operator - (const P&b) const {
		return P(x - b.x , y - b.y);
	}
	T operator / (const P&b) const {
		return x * b.y - y * b.x;
	}
	void read() {
		cin >> x >> y;
	}
};

T area(P a , P b, P c) {
	T res = (b - a) / (c - a);
	if(res < 0) res = -res;
	return res;
}

P p[3];

int main() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	ll x , y;
	while(cin >> x >> y) {
		p[0].x = x , p[0].y = y;
		rep(i,1,3) p[i].read();
		cout << area(p[0] , p[1] , p[2]) * 11 << endl;
	}
	return 0;
}


int main2() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	ll x , y;
	while(cin >> x >> y) {
		p[0].x = x , p[0].y = y;
		rep(i,1,3) p[i].read();
		ll times = 0;
		db sum = 0;
		rep(i,0,100000) rep(j,0,100000) if(i + j <= 100000){
			P O(i / 100000. , j / 100000.);
			times++;
			sum += max(max(area(O , p[0] , p[1]) , area(O , p[1] , p[2])) , area(O , p[0] , p[2]));
		}
		cout << sum / times * 36 << endl;
	}
	return 0;
}
