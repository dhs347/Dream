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

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

ll x,y;

int main() {
//	file_put(); 
	
	scanf("%lld%lld",&x,&y);
	if (x*y<=0) return 0*printf("%lld\n",abs(abs(x)-abs(y))+!(x<y && (!x || !y)));
	printf("%lld\n",abs(x-y)+(x>y)*2);
	
	return 0;
}

