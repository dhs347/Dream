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
typedef long double db;
typedef vector<int> vi;

const db eps = 1e-8, pi = acos(-1);

int sign(db x) {
  return (x > eps) - (x < -eps);
}

db ans;

struct P {
  db x, y;
  P() {}
  P(db x, db y) : x(x), y(y) {}
  P operator + (const P &c) const {
    return P(x + c.x, y + c.y);
  }
  P operator - (const P &c) const {
    return P(x - c.x, y - c.y);
  }
  P operator * (const db &c) const {
    return P(x * c, y * c);
  }
  P operator / (const db &c) const {
    return P(x / c, y / c);
  }
  P rot(const db ang) {
    return P(cos(ang) * x - sin(ang) * y, cos(ang) * y + sin(ang) * x);
  }
  db len() {
    return sqrt(x * x + y * y);
  }
  void print() {
    cout << x << " " << y << endl;
  }
};
struct L {
  P a, b;
  L() {}
  L(P a, P b) : a(a), b(b) {}
};
L cut;
db dot(P a, P b) {
  return a.x * b.x + a.y * b.y;
}
db det(P a, P b) {
  return a.x * b.y - a.y * b.x;
}
bool onSeg(const L &l, const P &p) {
  return sign(det(p - l.a, l.b - l.a)) == 0 && sign(dot(p - l.a, p - l.b)) <= 0;
}
void dfs(P a, P b, db len, int k) {
 // a.print(); b.print(); cout << endl;
  db s1 =  det(cut.b - cut.a, a - cut.a);
  db s2 = -det(cut.b - cut.a, b - cut.a);
  if(sign(s1) == 0 && sign(s2) == 0) {
    return ;
  } else {
    P p = (a * s2 + b * s1) / (s1 + s2);
    if(onSeg(L(a, b), p)) {
      ans += (p - b).len();
    } else {
      ans += (a - b).len();
      P t = (a - b) / 4;
      if(k > 1) {
      	dfs(t + a, a, len / 4, k - 1);
      	dfs(t.rot(pi / 3) + a, a, len / 4, k - 1);
      	dfs(t.rot(pi * 5 / 3) + a, a, len / 4, k - 1);
      }
    }
  }
}
void solve() {
  db len, n, x, y, k;
  cin >> len >> n >> x >> y >> k;
  cut = L(P(x, y), P(x + 10, y + k * 10));
  ans = 0;
  dfs(P(0, len), P(0, 0), len, n);
  cout << ans << endl;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cout << setiosflags(ios::fixed);
  cout << setprecision(6);
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
