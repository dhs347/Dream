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

const int N = 4, P = 1e9 + 7;

int add(int a, int b) {
  if((a += b) >= P) a -= P;
  return a;
}
int mul(int a, int b) {
  return 1ll * a * b % P;
}

struct Mat {
  int a[N][N];
  Mat() { memset(a, 0, sizeof(a)); }
  void Set() {
    rep(i, 0, N) a[i][i] = 1;
  }
  Mat operator * (const Mat &c) const {
    Mat r;
    rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
    return r;
  }
};

Mat kpow(Mat a, int b) {
  Mat r;
  r.Set();
  while(b) {
    if(b & 1) r = r * a;
    a = a * a;
    b >>= 1;
  }
  return r;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  cin >> n;
  Mat a;
  rep(i, 1, N) rep(j, 1, N) a.a[i][j] = 1;
  a = kpow(a, n - 1);
  int ans = 0;
  ans = add(ans, add(a.a[1][2], a.a[1][3]));
  ans = add(ans, add(a.a[3][2], a.a[3][3]));
  cout << ans << endl;
  return 0;
}
