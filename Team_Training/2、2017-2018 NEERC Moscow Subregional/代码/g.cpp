#include <bits/stdc++.h>
using namespace std;

const int _N=1e6+5,_M=1e6+5;
const int N=260005;
typedef vector<int> vi;
#define rep(i,a,b) for (int i=(a); i<=(b); ++i)
#define mem(a,x) memset(a,x,sizeof(a))
#define pb push_back
typedef long long ll;
vi V[N],E[N]; ll dist[N];
const ll oo=1e16;

struct SPFA{
	int x,cnt[_N],n; bool v[_N];
	void init(int _n) { n=_n; }
	bool solve(int s,ll dist[]){
		queue<int> Q;
		rep(i,0,n) dist[i]=-oo; int tot=0;
		mem(v,0),mem(cnt,0),dist[s]=0,cnt[s]=v[s]=1,Q.push(s);
		while (!Q.empty()){
			x=Q.front(),Q.pop(),v[x]=0;
			for (int i=0; i<(int)V[x].size(); ++i){
				int y=V[x][i];
				if (dist[x]+E[x][i]>dist[y]) {
					dist[y]=dist[x]+E[x][i];
					if (!v[y]) {
						if (cnt[y]>=n) return 0;
						Q.push(y),v[y]=1,cnt[y]++;
						tot++;
						if (tot>5e6) return 0;
					}
				}
			}
		}
		return 1;
	}
} T;


int n,m,x;

void I(int x,int y,int w){
	V[x].pb(y),E[x].pb(w);
}

int id(int x,int y){
	if (x<=0) x+=n;
	if (y<=0) y+=m;
	return (x-1)*m+y;
}

int c;

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,2*m) {
		scanf("%d",&c);
		if (j&1) {
			int a=i,b=(j+1)>>1;
			int x=id(a,b),y=id(a-1,b);
			I(y,x,c),I(x,y,-c);
		} else{
			int a=i,b=j>>1;
			int y=id(a,b),x=id(a,b-1);
			I(y,x,c),I(x,y,-c);
		}
	}
		rep(i,1,n*m) I(0,i,0);
		T.init(n*m);
		if (T.solve(0,dist)) printf("Yes\n"); else printf("No\n");

	return 0;
}
