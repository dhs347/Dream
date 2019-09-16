#include <bits/stdc++.h>
#include <map> 
#include <cstring>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define de(x) cout<<#x<<" = "<<x<<"\n"
#define dd(x) cout<<#x<<" = "<<x<<" "
#define mes(p) memset(p,0,sizeof(p))
#define all(x) x.begin(),x.end()
#define rson mid+1,r,rt<<1|1
#define sz(x) (int)x.size()
#define lson l,mid,rt<<1
#define pb push_back
#define mp make_pair
#define ls (rt<<1)
#define se second
#define rs (ls|1)
#define fi first
typedef pair <int ,int > pi;
typedef vector <int > vi;
typedef long long ll;
const int maxn=3000005;
const ll mod = 1e9+ 7;

const int N = 1010101;

int n, b;
ll pre[11][N];

ll calc(int x, int b) {
	ll ans = 0;
	while(x) {
		ans += x % b;
		x /= b;
	}
	return ans;
}

int main(){	
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    rep(b, 2, 11) rep(i, 1, N) pre[b][i] = pre[b][i - 1] + calc(i, b);
    int T; cin >> T;
    int ca = 0;
    while(T--) {
    	int n, b; cin >> n >> b;
    	cout << "Case #" << ++ca << ": ";
    	cout << pre[b][n] << endl;
	}
	return 0;
}
