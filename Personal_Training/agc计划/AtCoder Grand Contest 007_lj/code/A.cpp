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

int n,m,x,y,xx,yy; char s[15][15];

int main() {
//	file_put();
	
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) scanf("%s",s[i]+1);
	x=1,y=1; s[x][y]='.';
	while (!(x==n && y==m)) {
		xx=x,yy=y;
		while (x<=n && y+1<=m && s[x][y+1]=='#') y++,s[x][y]='.';
		while (x+1<=n && y<=m && s[x+1][y]=='#') x++,s[x][y]='.';
		if (xx==x && yy==y) break;
	}
	rep(i,1,n+1) rep(j,1,m+1) if (s[i][j]=='#') return 0*printf("Impossible\n");
	printf("Possible\n");
	
	return 0;
}

