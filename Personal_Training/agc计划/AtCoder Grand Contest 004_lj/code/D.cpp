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

#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n) rep(j,0,m) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=1e5+5; 
int n,ans=0,a[N],k; bool v[N]; int f[N][20],id[N],p[N],dep[N]; vi V[N];

int G(int x,int k) {
	per(i,0,20) if (k>>i&1) x=f[x][i];
	return x;
}

void dfs(int x,int d) {
	v[x]=1; if (dep[x]==-1) dep[x]=d;
	for (auto y:V[x]) if (!v[y]) dfs(y,d+1);
}

bool cmp(int x,int y) {
	return dep[x]>dep[y];
}

int main() {
//	file_put();
	
	scanf("%d%d",&n,&k);
	rep(i,1,n+1) scanf("%d",&a[i]);
	ans=(a[1]!=1),a[1]=1;
	rep(i,2,n+1) V[a[i]].pb(i);
	memset(dep,-1,sizeof(dep)); 
	dfs(1,0); memset(v,0,sizeof(v)); 
	if (k>=n-1) return 0*printf("%d\n",ans);
	rep(i,1,n+1) f[i][0]=a[i];
	rep(i,1,20) rep(j,1,n+1) f[j][i]=f[f[j][i-1]][i-1];
	rep(i,1,n+1) p[i]=G(i,k-1),id[i]=i;
	sort(id+1,id+n+1,cmp);
	rep(i,1,n+1) {
		if (dep[id[i]]<=k) break;
		if (v[id[i]]) continue;
		if (a[p[id[i]]]==1) continue;
		ans++;
		dfs(p[id[i]],0);
//		debug_arr(dep,n);
	}
	printf("%d\n",ans);
	
	return 0;
}

