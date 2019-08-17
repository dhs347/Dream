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

ll s,x[4],y[4],t;

int main() {
//	file_put();
	
	scanf("%lld",&s);
	for (t=(ll)sqrt(s); t*t<s; t++);
	x[3]=t*t-s,y[2]=1;
	x[2]=y[3]=t;
	rep(i,1,4) printf("%lld %lld ",x[i],y[i]);
	printf("\n"); 
	
	return 0;
}

