// [1,n] , init!!
template<class T>
struct Fenwick{
#define lb(x) ((x)&-(x))
    static const int N = 100001;
    int n;T a[N];
    void ini(int _n){ fill_n(a+1,n=_n,0);}
    void Pre(){ for(int i=1,j=i+lb(i);i<=n;++i,j=i+lb(i)) if(j<=n) a[j]+=a[i];}
    void add(int x,T d){ for(;x<=n;x+=lb(x)) a[x]+=d;}
    T sum(int x){ T r=0;for(;x>=1;x^=lb(x)) r+=a[x];return r;}
};
