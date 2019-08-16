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

const int N=2e4+5;
int n,a[N],b[N],p[N],k;

int main() {
//	file_put();
	
	scanf("%d",&n),a[1]=b[1]=1;
	rep(i,1,n+1) scanf("%d",&p[i]);
	rep(i,2,n+1) a[i]=b[i]=a[i-1]+n;
	reverse(b+1,b+n+1);
	rep(i,2,n+1) a[p[i]]+=i-1;
	rep(i,1,n+1) printf("%d%c",a[i]," \n"[i==n]);
	rep(i,1,n+1) printf("%d%c",b[i]," \n"[i==n]);
	
	return 0;
}

