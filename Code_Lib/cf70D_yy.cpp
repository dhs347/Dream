#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

struct P {
	int x, y;
	P() {}
	P(int x, int y) : x(x), y(y) {}
};
namespace DCH {
	map<int, P> h1, h2;
	bool ao(P a, P b, P c) {
		return (b.y - a.y) * 1ll * (c.x - b.x) <= (c.y - b.y) * 1ll * (b.x - a.x);
	}
	bool in(map<int, P> &h, P p) {
		if(!sz(h)) return 0;
		if(p.x < h.begin()->se.x || p.x > h.rbegin()->se.x) return 0;
		auto l = h.lower_bound(p.x);
		if(p.x == l->se.x) return p.y <= l->se.y;
		auto r = l--;
		return ao(l->se, p, r->se);
	}
	void ins(map<int, P> &h, P p) {
		if(in(h, p)) return ;
		h[p.x] = p;
		auto pos = h.find(p.x);
		while(1) {
			auto l = pos; if(l == h.begin()) break; --l;
			auto ll = l; if(ll == h.begin()) break; --ll;
			if(ao(ll->se, l->se, p)) h.erase(l); else break;
		}
		while(1) {
			auto r = pos; r++; if(r == h.end()) break;
			auto rr = r; rr++; if(rr == h.end()) break;
			if(ao(p, r->se, rr->se)) h.erase(r); else break;
		}
	}
	void ins(int x, int y) { ins(h1, P(x, y)); ins(h2, P(x, -y)); }
	bool in(int x, int y) { return in(h1, P(x, y)) && in(h2, P(x, -y)); }
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; cin >> n;
	rep(i, 1, n + 1) {
		int o, x, y;
		cin >> o >> x >> y;
		if(o == 1) {
			DCH::ins(x, y);
		} else {
			cout << (DCH::in(x, y) ? "YES" : "NO") << endl;
		}
	}
	return 0;
}
