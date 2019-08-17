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
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=5e5+5;
int n,a[N],f[N],g[41][N],id[N],c[N],tot=0; bool v[N]; ll k;

inline int o(int x) { ++x; if (x>n) x=1; return x; } 

int G(int x,ll k) {
	per(i,0,41) if (k>>i&1) x=g[i][x];
	return x;
}

int main() {
//	file_put();
	
//	srand(time(0));
	scanf("%d%lld",&n,&k);
	rep(i,1,n+1) scanf("%d",&a[i]),a[i+n]=a[i];
//	rep(i,1,n+1) a[i]=rand(),a[i+n]=a[i];
	per(i,n+1,2*n+1) id[a[i]]=i-n;
	per(i,1,n+1) {
		if (id[a[i]]<=i) f[i]=id[a[i]]+1; else
			if (o(id[a[i]])==1) f[i]=1; else f[i]=f[o(id[a[i]])];
		id[a[i]]=i;
	}
	f[n+1]=1;
	rep(i,1,n+2) g[0][i]=f[i];
	rep(i,1,41) rep(j,1,n+2) g[i][j]=g[i-1][g[i-1][j]];
	int p=G(1,k-1);
	rep(i,p,n+1) {
		if (!v[a[i]]) v[a[i]]=1,c[++tot]=a[i];
		else while (tot && v[a[i]]) v[c[tot--]]=0;
	}
	rep(i,1,tot+1) printf("%d%c",c[i]," \n"[i==tot]);
	
//	memset(v,0,sizeof(v)),tot=0;
//	rep(p,1,k+1) rep(i,1,n+1) {
//		if (!v[a[i]]) v[a[i]]=1,c[++tot]=a[i];
//		else while (tot && v[a[i]]) v[c[tot--]]=0;
//	} 
//	rep(i,1,tot+1) printf("%d%c",c[i]," \n"[i==tot]);
//	
//	debug_arr(a,n);
//	debug_arr(f,n+1);
//	debug_arr2(g,10,n+1);
//	debug(p);
	
	
	return 0;
}

