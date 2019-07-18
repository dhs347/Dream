#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i--)
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

const int N = 1e5 + 10;
int n;
struct P {
	int x , y , a , b;
	bool operator < (const P&b) const {
		if(x != b.x) return x < b.x;
		return y > b.y;
	}
} p[N];

struct Fenwick {
	int n;
	ll a[N];
	void init(int _n) {
		n = _n;
		rep(i,0,n+1) a[i] = 0;
	}
	void add(int x,ll t) {
		for(;x<=n;x+=x&-x) a[x]+=t;
	}
	ll sum(int x) {
		ll r=0;for(;x>=1;x-=x&-x) r+=a[x];return r;
	}
	void add(int l,int r,ll t) {
		add(l , t);
		add(r + 1 , -t);
	}
} fen;

#define order(x) sort(all(x));x.erase(unique(all(x)),x.end())
#define rk(x,a) upper_bound(all(x),a)-x.begin()

int main() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	while(cin >> n) {
		vi Vy(n , 0);
		rep(i,0,n) {
			cin >> p[i].x >> p[i].y >> p[i].a >> p[i].b;
			p[i].y = -p[i].y;
			Vy[i] = p[i].y;
		}
		order(Vy);
		ll res = 0;
		rep(i,0,n) res += p[i].b;
		rep(i,0,n) p[i].a -= p[i].b;
		rep(i,0,n) p[i].y=rk(Vy,p[i].y);
		sort(p , p + n);
		set<int> key;
		key.insert(0);
		fen.init(sz(Vy));
		ll mx = 0;
		for(int j=0,i=j;j<n;j=i) {
			for(i=j;i<n&&p[i].x==p[j].x;++i);
			for(int k=j;k<i;++k) {
				ll del = p[k].a;
				fen.add(p[k].y , sz(Vy) , del);
				if(!key.count(p[k].y)) key.insert(p[k].y);
				if(!key.count(p[k].y - 1)) key.insert(p[k].y - 1);
			}
			for(int k=i-1;k>=j;--k) {
				auto e = key.find(p[k].y);
				--e;
				ll cur = fen.sum(p[k].y);
				int last = p[k].y;
				ll predel = 0;
				for(;;key.erase(e--)) {
					fen.add(*e + 1 , last , predel);
					ll get = fen.sum(*e);
					//cout << p[i].y << " " << *e << " " << get << " " << cur << endl;
					if(get > cur) {
						break;
					} else {
						predel = cur - get;
						last = *e;
					}
					if(*e == 0) break;
				}
			}
			if(sz(key) > 1) {
				auto e = key.begin();
				++e;
				mx = max(mx , fen.sum(*e));
			}
			/*
			for(auto e : key) {
				cout << e << " " << fen.sum(e) << endl;
			}
			cout << "~~~~~~~~~~~~~~" << endl;
			*/
		}
		res += mx;
		cout << res << endl;
	}
	return 0;
}
