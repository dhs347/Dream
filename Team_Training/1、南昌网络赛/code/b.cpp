#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010, inf = 1e9 + 7;

int n, q;

struct Seg {
#define ls rt << 1
#define rs ls | 1
  static const int N = ::N << 2;
  int mi[N];
  ll sum[N];
  ll qry(int L, int R, int &v, bool spe, int l, int r, int rt) {
    if(!spe) {
      if(mi[rt] >= v) return 0;
      if(L <= l && r <= R) {
      	if(l == r) return v = mi[rt];
      	int mid = l + r >> 1;
      	if(mi[ls] >= v) return qry(L, R, v, 0, mid + 1, r, rs);
      	ll ans = sum[rt] - sum[ls] + qry(L, R, v, 0, l, mid, ls);
      	return v = mi[rt], ans;
      }
    }
    int mid = l + r >> 1;
    ll ans = 0;
    if(L <= mid) ans += qry(L, R, v, 0, l, mid, ls);
    if(R > mid) ans += qry(L, R, v, 0, mid + 1, r, rs);
    return ans;
  }
  void up(int l, int r, int rt) {
    mi[rt] = min(mi[ls], mi[rs]);
    int v = inf;
    sum[rt] = qry(l, r, v, 1, l, r, rt);
  }
  void build(int l, int r, int rt) {
    if(l == r) {
      cin >> mi[rt];
      sum[rt] = mi[rt];
   //   dd(l), dd(r), de(sum[rt]);
      return ;
    }
    int mid = l + r >> 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    up(l, r, rt);
 //   dd(l), dd(r), de(sum[rt]);
  }
  void upd(int p, int c, int l, int r, int rt) {
    if(l == r) {
      mi[rt] = sum[rt] = c;
      return ;
    }
    int mid = l + r >> 1;
    if(p <= mid) upd(p, c, l, mid, ls);
    else upd(p, c, mid + 1, r, rs);
    up(l, r, rt);
  }
}seg;

void solve() {
  cin >> n >> q;
  seg.build(1, n, 1);
  while(q--) {
    int l, r, p, c, v = inf;
    cin >> l >> r >> p >> c;
//    ll ans;
//    rep(i, 1, n + 1) rep(j, i, n + 1) ans = seg.qry(i, j, v = inf, 0, 1, n, 1), dd(i), dd(j), de(ans);
    cout << seg.qry(l, r, v, 0, 1, n, 1) << endl;
    if(p) seg.upd(p, c, 1, n, 1);
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
