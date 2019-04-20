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

const int N = 105;
int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
ll h[20], f[N][N * 8];
int T, l, r, k, m, a[N], n, pre;
string s;


bool check(int num, int len) {
  return num >= len * 2 && num <= len * 7;
}

int cal(int num, int len, int o) {
  int res = 0;
  if (o == 1) {
    rep(i, 1, len+1) {
      res *= 10;
      per(j, 0, 10) {
	if (check(num - c[j], len - i)) {
	  res += j; num -= c[j];
	  break;
	}
      }
    } 
    return res;
  }else {
    if (num == len * 2 + 1) return h[len];
    num -= 2;
    rep(i, 1, len+1) {
      res *= 10;
      per(j, 0, 10) {
	if (check(num - c[j], len - i)) {
	  res += j; num -= c[j];
	  break;
	}
      }
    } 
    return res;
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> T;
  h[1] = -1;
  rep(i, 2, 12) h[i] = h[i-1] * 10 - 1;
  rep(cas, 0, T) {
    cin >> n >> s;
    pre = -1;k = 0;m = 0;
    rep(i, 0, n) if (s[i] == '-' || s[i] == '+'){
      if (s[i] == '-') m ++;else m += 2;
      a[++k] = i - pre - 1;
      pre = i;
    } else m += c[s[i] - '0'];
    a[++k] = n - pre - 1;
    rep(i, 0, k+1) rep(j, 0, m+1) f[i][j] = -pw(60);
    f[0][0] = 0;
    rep(i, 1, k+1) {
      if (i == 1) {
	l = a[i] * 2; r = a[i] * 7;
      } else l = a[i] * 2 + 1, r = a[i] * 7 + 2;
      rep(num, 0, m+1) rep(j, l, r+1) if (num - j >= 0) f[i][num] = max(f[i][num], f[i-1][num - j] + cal(j, a[i], (i == 1)));
    }
    cout << f[k][m] << endl;
  }
  return 0;
}
