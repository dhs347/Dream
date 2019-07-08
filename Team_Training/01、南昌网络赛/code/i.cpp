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


const int N = 5e5 + 10;

ll tma[N * 4], tmi[N * 4], ma, mi, ans, tmp, s[N];
int a[N], n, L[N], R[N];
stack<pii> sta;

#define ls (now << 1)
#define rs ((ls) + 1)

void build(int l, int r, int now) {
  if (l == r) {
    tma[now] = tmi[now] = s[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, ls);
  build(mid+1, r, rs);
  tma[now] = max(tma[ls], tma[rs]);
  tmi[now] = min(tmi[ls], tmi[rs]);
}


void qry(int l, int r, int now, int L, int R) {
  if (L <= l && R >= r) {
    ma = max(ma, tma[now]);
    mi = min(mi, tmi[now]);
    return;
  }
  int mid = (l + r) >> 1;
  if (L <= mid) qry(l, mid, ls, L, R);
  if (R > mid) qry(mid+1, r, rs, L, R);
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n;
  rep(i, 1, n+1) cin >> a[i], s[i] = s[i-1] + a[i];
  a[n+1] = -pw(30);
  rep(i, 1, n+2) {
    while (!sta.empty() && sta.top().fi > a[i]) {
      R[sta.top().se] = i - 1;
      sta.pop();
    }
    sta.push(mp(a[i], i));
  }
  sta.pop();
  a[0] = -pw(30);
  per(i, 0, n+1) {
    while (!sta.empty() && sta.top().fi > a[i]) {
      L[sta.top().se] = i + 1;
      sta.pop();
    }
    sta.push(mp(a[i], i));
  }
  sta.pop();
  build(0, n, 1);
  ans = -pw(60);
  rep(i, 1, n+1) {
    if (a[i] < 0) {
      ma = -pw(60); qry(0, n, 1, L[i]-1, i-1);
      tmp = ma;
      mi = pw(60); qry(0, n, 1, i, R[i]);
      ans = max(ans, (mi - tmp) * a[i]);
    }else if (a[i] > 0) {
      mi = pw(60); qry(0, n, 1, L[i]-1, i-1);
      tmp = mi;
      ma = -pw(60); qry(0, n, 1, i, R[i]);
      ans = max(ans, (ma - tmp) * a[i]);
    }
    else ans = max(ans, 0ll);
  }
  cout << ans << endl;
  return 0;
}
