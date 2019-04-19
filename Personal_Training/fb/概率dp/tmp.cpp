#include<cstdio>
#include<cstring>
char buf[10005];
int cnt[26];
double g[10005];
double f[10005],k[10006],b[10005];
int main(){
freopen("a.in","r",stdin);
  scanf("%s",buf);
  for(int i=0;buf[i]!='\0';++i)cnt[buf[i]-'A']++;
  int n=strlen(buf);
  for(int i=1;i<n;++i){
    g[i]=(n*n-n)/2.0/i/(n-i);
  }
  //  g[1]=(n*n-1*(n-1))/double(n-1);
  f[n]=0;
  k[1]=1;b[1]=g[1];
  for(int i=2;i<n;++i){
    b[i]=b[i-1]*(i-1)/2.0/i+g[i];
    k[i]=(i+1)/2.0/i;
    k[i]=k[i]/(1-k[i-1]*(i-1)/2.0/i);
    b[i]=b[i]/(1-k[i-1]*(i-1)/2.0/i);
  }
  for(int i=n-1;i>=1;--i){
    f[i]=f[i+1]*k[i]+b[i];
  }
  double ans=0;
  for(int i=0;i<26;++i){
    ans+=cnt[i]/double(n)*f[cnt[i]];
  }
  printf("%.1f\n",ans);
  return 0;
}
