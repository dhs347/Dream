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

const int N=3e5+5,oo=1e9;
int n,q,x,y,a[N],f[N][20],g[20];

int main() {
	//file_put();
	
	scanf("%d%d",&n,&q);
	rep(i,1,n+1) scanf("%d",&a[i]);
	rep(i,0,20) g[i]=oo;
	rep(i,1,n+1) rep(j,0,20) f[i][j]=oo;
	per(i,1,n+1) {
		rep(j,0,20) if (a[i]>>j&1) f[i][j]=i;
		rep(j,0,20) if (a[i]>>j&1) {
			if (g[j]>n) continue;
			rep(k,0,20) f[i][k]=min(f[i][k],f[g[j]][k]);
		}
		rep(j,0,20) if (a[i]>>j&1) g[j]=i;
	}
	rep(i,1,q+1) {
		scanf("%d%d",&x,&y);
		bool ok=0;
		rep(c,0,20) if ((a[y]>>c&1) && f[x][c]<=y) {
			printf("Shi\n");
			ok=1;
			break; 
		}
		if (!ok) printf("Fou\n");
	}
	
	return 0;
}

