#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=' ';
}
const int N=3e5+5,P=998244353,inv2=499122177,G=3;
typedef int arr[N];
typedef unsigned long long ll;
int n,pw,K;arr a,b,c,d,e,wn,inv,pos;
inline int pls(int a,int b){return a+=b,a<P?a:a-P;}
inline int sub(int a,int b){return a-=b,a<0?a+P:a;}
inline int fpm(int a,int b){int x=1;for(;b;b>>=1,a=(ll)a*a%P)if(b&1)x=(ll)x*a%P;return x;}
inline void init(){
    for(int i=0;i<K;++i)pos[i]=(i&1)?((pos[i>>1]>>1)^(K>>1)):(pos[i>>1]>>1);
    register int L=K>>1;wn[L]=1;wn[L+1]=fpm(G,(P-1)/K);
    fp(i,2,L-1)wn[L+i]=(ll)wn[L+i-1]*wn[L+1]%P;
    fd(i,L-1,1)wn[i]=wn[i<<1];
}
inline void dft(int*a,int ty=1){
    fp(i,0,K-1)(i<pos[i])&&(swap(a[i],a[pos[i]]),0);
    for(int i=2;i<=K;i<<=1){
        const register int d=i>>1,*w=wn+d;int o;
        for(register int*x=a,*y=x+d;x!=a+K;x+=i,y+=i)fp(k,0,d-1)
            o=(ll)y[k]*w[k]%P,y[k]=sub(x[k],o),x[k]=pls(x[k],o);
    }if(ty^1){
        reverse(a+1,a+K);
        const int inv=fpm(K,P-2);
        fp(i,0,K-1)a[i]=(ll)a[i]*inv%P;
    }
}
inline void Mul(int*a,int*b){dft(a),dft(b);fp(i,0,K-1)a[i]=(ll)a[i]*b[i]%P;dft(a,-1);}
void Inv(int*a,int*b,int L){
    if(L==1)return b[0]=fpm(a[0],P-2),void();
    Inv(a,b,L>>1);K=L<<1;init();
    fp(i,0,L-1)c[i]=a[i];fp(i,L,K-1)c[i]=0;
    fp(i,(L>>1),K-1)b[i]=0; dft(b),dft(c);
    fp(i,0,K-1)b[i]=(ll)b[i]*sub(2,(ll)b[i]*c[i]%P)%P;
    dft(b,-1);fp(i,L,K-1)b[i]=0;
}
void Sqrt(int*a,int*b,int L){
    if(L==1)return b[0]=sqrt(a[0]),void();
    Sqrt(a,b,L>>1);Inv(b,d,L);K=L<<1;init();
    fp(i,0,L-1)e[i]=a[i];fp(i,L,K-1)e[i]=0;
    Mul(e,d);fp(i,L,K-1)b[i]=0;
    fp(i,0,L-1)b[i]=pls((ll)b[i]*inv2%P,(ll)e[i]*inv2%P);
}
inline void Ln(int*a,int*b,int L){
    Inv(a,d,L);K=L<<1;init();
    fp(i,0,L-2)b[i]=(ll)a[i+1]*(i+1)%P;
    fp(i,L-1,K-1)b[i]=0;Mul(b,d);
    fd(i,L-1,1)b[i]=(ll)b[i-1]*inv[i]%P;
    fp(i,L,K-1)b[i]=0;b[0]=0;
}
void Exp(int*a,int*b,int L){
    if(L==1)return b[0]=exp(a[0]),void();
    Exp(a,b,L>>1);Ln(b,e,L);K=L<<1;init();
    fp(i,0,L-1)e[i]=sub(a[i],e[i]);++e[0];
    fp(i,L,K-1)e[i]=b[i]=0;Mul(b,e);
    fp(i,L,K-1)b[i]=0;
}
int main(){
    #ifndef ONLINE_JUDGE
        file("polynomial");
    #endif
    sd(n);sd(pw);
    fp(i,0,n-1)sd(a[i]);wn[0]=inv[1]=1;
    fp(i,2,n)inv[i]=(ll)(P-P/i)*inv[P%i]%P;
    int L=1;while(L<n)L<<=1;Sqrt(a,b,L);Inv(b,a,L);
    fd(i,n-1,1)a[i]=(ll)a[i-1]*inv[i]%P;a[0]=0;
    Exp(a,b,L);Inv(b,a,L);++a[0];Ln(a,b,L);++b[0];
    Ln(b,a,L);fp(i,0,n-1)a[i]=(ll)a[i]*pw%P;Exp(a,b,L);
    fp(i,0,n-1)b[i]=(ll)b[i+1]*(i+1)%P;b[n-1]=0;
    fp(i,0,n-1)we(b[i]);
return Ot(),0;
}
