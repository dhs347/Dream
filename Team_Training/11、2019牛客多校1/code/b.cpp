#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i++)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << " "
#define dd(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 1010 , P = 1e9 + 7;
int Pow(int x,int t){int r=1;for(;t;t>>=1,x=ll(x)*x%P)if(t&1)r=ll(r)*x%P;return r;}
int inv(int x) {return Pow(x , P - 2);}
void pp(int &x,int d) {if((x+=d)>=P)x-=P;}
int a[N] , pa[N];

int main() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	int n;
	while(cin >> n) {
		rep(i,0,n) cin >> a[i] , pa[i] = ll(a[i]) * a[i] % P;
		int res = 0;
		rep(i,0,n) {
			int cof = 1;
			rep(j,0,n) if(i != j) {
				int ecof = pa[j];
				pp(ecof , P - pa[i]);
				cof = ll(cof) * ecof % P;
			}
			cof = 2ll * cof % P;
			cof = 1ll * cof * a[i] % P;
			cof = inv(cof);
			pp(res , cof);
		}
		cout << res << endl;
	}
	return 0;
}
