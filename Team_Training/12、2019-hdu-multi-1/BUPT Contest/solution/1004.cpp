#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

const int maxn=2e5+5;

struct DR{
  int id;
  double nt;
  bool operator > (const DR &Vt)const{
    return nt>Vt.nt;
  }
};

priority_queue<DR,vector<DR>,greater<DR>> sq;

bool vis[maxn];
double d[maxn],t[maxn];
int l[maxn],s[maxn],v[maxn];
int f[maxn],sl[maxn];
int n;

int Find(int x){
  return f[x]==x?x:f[x]=Find(f[x]);
}

int main(){
  ios::sync_with_stdio(false);
  while( cin >> n ){
    for(int i=0;i<=n;++i) cin >> l[i] ;
    for(int i=0;i<=n;++i) cin >> s[i] ;
    for(int i=0;i<=n;++i) cin >> v[i] ;
    for(int i=0;i<=n;++i) sl[i]=i;
    for(int i=0;i<=n;++i) f[i]=i;
    for(int i=0;i<=n;++i) vis[i]=false;
    for(int i=0;i<=n;++i) t[i]=0;
    for(int i=0;i<n;++i) d[i]=s[i]-s[i+1]-l[i+1];
    for(int i=0;i<n;++i){
      if( v[i]>v[i+1] ){
        sq.push(DR{i,d[i]/(v[i]-v[i+1])});
      }
    }
    double cd=0,cv=v[0],ct=0;
    while( !sq.empty() ){
      DR tp=sq.top();sq.pop();
      if( vis[tp.id] ) continue;
      vis[tp.id]=true;
      if( cd+cv*(tp.nt-ct)>=s[0] ){
        ct+=(s[0]-cd)/cv;
        cd=s[0];
        break;
      }
      cd+=cv*(tp.nt-ct);
      ct=tp.nt;
      int p=tp.id;
      f[p]=Find(p+1);
      if( sl[p]==0 ) cv=v[f[p]];
      sl[Find(p+1)]=sl[p];
      d[sl[p]-1]-=(v[sl[p]-1]-v[p])*(tp.nt-t[sl[p]-1]);
      t[sl[p]-1]=tp.nt;
      if( v[sl[p]-1]>v[f[p]] )
        sq.push(DR{sl[p]-1,d[sl[p]-1]/( v[sl[p]-1]-v[f[p]] )+tp.nt});
    }
    while( !sq.empty() ) sq.pop();
    if( cd!=s[0] ) ct+=(s[0]-cd)/cv;
    cout << fixed << setprecision(10) << ct << endl ;
  }
  return 0;
}
