#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 303030;

int n, h[N], rt, st[N], ed[N], top;
ll L, R, ans[N];

// desc : bud a cartesion tree from a[0] .. a[n - 1]
// time : O(N)
// !!!! : return rt, a[n] will be rewrite
int ls[N], rs[N];
int ct(int a[], int n) {
	a[n] = 0;
	vi v(1, n);
	fill_n(ls, n, -1), fill_n(rs, n, -1);
	rep(i, 0, n) {
		while (a[v.back()] > a[i])
			ls[i] = v.back(), v.pop_back();
		v.pb(rs[v.back()] = i);
	}
	return v[1];
}

ll calc(ll c) {
	ll cnt = 0;
	rep(i, 1, n + 1) {
		int l = st[i], r = ed[i];
		int fr = 1, to = min(c / h[i], r - l + 1ll);
		if(fr > to) continue;
		int x = r - i + 1, y = i - l + 1;
		int l1 = max(fr, max(x, y)), r1 = to;
		int l2 = fr, r2 = min(to, min(x - 1, y - 1));
		int l3 = max(fr, y), r3 = min(to, x - 1);
		int l4 = max(fr, x), r4 = min(to, y - 1);
		if(l1 <= r1) {
		//	dd(l1), de(r1);
			cnt += (r - l + 2) * 1ll * (r1 - l1 + 1);
			cnt -= (l1 + r1) * 1ll * (r1 - l1 + 1) / 2;
		}
		if(l2 <= r2) {
			//dd(l2), de(r2);
			cnt += (l2 + r2) * 1ll * (r2 - l2 + 1) / 2;
		}
		if(l3 <= r3) {
		//	dd(l3), de(r3);
			cnt += (i - l + 1) * 1ll * (r3 - l3 + 1);
		}
		if(l4 <= r4) {
			//dd(l4), de(r4);
			cnt += (r - i + 1) * 1ll * (r4 - l4 + 1);
		}
	//	dd(i), dd(fr), dd(to), dd(l), dd(r), de(cnt - pre);
	}
	return cnt;
}

void solve(ll L, ll R) {
	rep(i, 1, n + 1) {
		int l = st[i], r = ed[i];
		int fr = max(1ll, (L + h[i] - 1) / h[i]), to = min(r - l + 1ll, R / h[i]);
		if(fr > to) continue;
		rep(w, fr, to + 1) {
			int cnt = min(i + w - 1, r) - max(i - w + 1, l) - w + 2;
			if(cnt > 0) {
				while(cnt--) ans[++top] = h[i] * 1ll * w;
			}
		}
	}
}

// >= x
pair<ll, ll> gao(ll x) {
	ll l = 1, r = 3e14, res = 0, ans = 0;
	while(l <= r) {
		ll mid = l + r >> 1;
		ll t = calc(mid);
		if(t >= x) {
			res = mid, ans = t;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
//	dd(res), de(ans);
	return mp(res, ans);
}

void dfs(int u) {
	st[u] = ed[u] = u;
	if(ls[u]) {
		dfs(ls[u]);
		st[u] = min(st[u], st[ls[u]]);
		ed[u] = max(ed[u], ed[ls[u]]);
	}
	if(rs[u]) {
		dfs(rs[u]);
		st[u] = min(st[u], st[rs[u]]);
		ed[u] = max(ed[u], ed[rs[u]]);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> h[i];
	cin >> L >> R;
	rt = ct(h + 1, n) + 1;
	rep(i, 0, n) ++ls[i], ++rs[i];
	per(i, 1, n + 1) ls[i] = ls[i - 1], rs[i] = rs[i - 1];
	dfs(rt);
	pair<ll, ll> st = gao(L), ed = gao(R);
	int to = min(st.se, R) - L + 1;
	while(to--) ans[++top] = st.fi;
//	de(top);
	solve(st.fi + 1, ed.fi - 1);
	//de(top);
	while(top < R - L + 1) ans[++top] = ed.fi;
//	de(top);
	sort(ans + 1, ans + 1 + top);
	rep(i, 1, top + 1) cout << ans[i] << " \n"[i == top];
	return 0;
}
