#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 505050, M = 21;

int n, k, L, R;
int a[N];
ll ans;
ll pre[N];
priority_queue<pair<pair<ll, int>, pii> > que;

pii ma[M][N]; int lg[N];

pii qry(int l, int r) {
  int i = lg[r - l + 1];
  return max(ma[i][l], ma[i][r + 1 - (1 << i)]);
}

void add(int l, int r, int i) {
  pii t = qry(l, r);
  ll c = t.fi - pre[i - 1];
  que.push(mp(mp(c, i), mp(l, r)));
}

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  cin >> n >> k >> L >> R;
  rep(i, 1, n + 1) cin >> a[i], pre[i] = pre[i - 1] + a[i];
  rep(i, 2, n + 1) lg[i] = lg[i >> 1] + 1;
  rep(i, 1, n + 1) ma[0][i] = mp(pre[i], i);
  rep(i, 1, lg[n] + 1) rep(j, 1, n - (1 << i) + 2) {
    ma[i][j] = max(ma[i - 1][j], ma[i - 1][j + (1 << i >> 1)]);
  }
  rep(i, 1, n + 1) {
    int l = max(0, L + i - 1), r = min(n, R + i - 1);
    if(l <= r) add(l, r, i);
  }
  rep(i, 1, k + 1) {
    pair<pair<ll, int>, pii> u = que.top();que.pop();
    ans += u.fi.fi;
    int l = u.se.fi, r = u.se.se;
    pii t = qry(l, r);
    int mid = t.se;
    if(l <= mid - 1) add(l, mid - 1, u.fi.se);
    if(mid + 1 <= r) add(mid + 1, r, u.fi.se);
  }
  cout << ans << endl;
  return 0;
}
