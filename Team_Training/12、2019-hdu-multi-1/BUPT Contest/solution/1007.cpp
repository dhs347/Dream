#include <bits/stdc++.h>

typedef std::pair<long long,long long> Frac;

Frac operator + (Frac a,Frac b) {
    long long y=a.second/std::__gcd(a.second,b.second)*b.second,
               x=a.first*(y/a.second)+b.first*(y/b.second);
    return {x,y};
}

Frac operator /(Frac a,int b) {
    long long x=a.first,y=a.second*b,
               d=std::__gcd(x,y);
    return {x/d,y/d};
}

const int N=1e6,XN=N+11;

int prime[XN],mu[XN],mert[XN],pcnt;

void Prep() {
    static bool notPrime[XN];
    mu[1]=1;
    for(int i=2;i<=N;++i) {
        if(!notPrime[i]) {
            prime[++pcnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=pcnt && i*prime[j]<=N;++j) {
            notPrime[i*prime[j]]=1;
            if(i%prime[j]==0) {
                mu[i*prime[j]]=0;
                break;
            } else
                mu[i*prime[j]]=-mu[i];
        }
    }
    for(int i=1;i<=N;++i)
        mert[i]=mert[i-1]+mu[i];
}

long long Sum(long long n,long long a,long long b,long long m) {
    if(b==0)
        return n*(a/m);
    else if(a>=m)
        return n*(a/m)+Sum(n,a%m,b,m);
    else if(b>=m)
        return (n-1)*n/2*(b/m)+Sum(n,a,b%m,m);
    else
        return Sum(((__int128)b*n+a)/m,(a+(__int128)b*n)%m,m,b);
}

long long Count(Frac x,int n) {
    long long res=0;
    for(int l=1,r;l<=n;l=r+1) {
        r=n/(n/l);
        res+=Sum(n/l+1,0,x.first,x.second)*(mert[r]-mert[l-1]);
    }
    return res;
}

Frac Gen(long long a,long long b,int n,long long k) {
    Frac l{0,1},mid{1,1},r{1,0},res{-1,-1};
    long long x=a,y=b;
    while(x!=y && std::max(mid.first,mid.second)<=n) {
        if(a*mid.second<b*mid.first)
            res=mid;
        if(x<y) {
            std::tie(l,mid,r)=std::make_tuple(l,std::make_pair(l.first+mid.first,l.second+mid.second),mid);
            y-=x;
        } else {
            std::tie(l,mid,r)=std::make_tuple(mid,std::make_pair(mid.first+r.first,mid.second+r.second),r);
            x-=y;
        }
    }
	assert(Count(res,n)==k);
    return res;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    Prep();
    int T;std::cin>>T;
    while(T--) {
        int n;long long k;
        std::cin>>n>>k;
        Frac l{0,1},r{1,1},pivot{-1,-1};
        for(int t=40;t--;) {
            Frac mid=(l+r)/2;
            if(Count(mid,n)<k) {
                pivot=mid;
                l=mid;
            } else
                r=mid;
        }
        auto Ans=Gen(pivot.first,pivot.second,n,k);
        std::cout<<Ans.first<<'/'<<Ans.second<<'\n';
    }
    return 0;
}
