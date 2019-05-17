#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N=100015*3;
const ll mod=998244353;
const int inv_2=499122177;

inline int read() {
	int x=0;
	char ch=getchar();
	while(ch<'0' || '9'<ch)ch=getchar();
	while('0'<=ch && ch<='9')x=x*10+(ch^48),ch=getchar();
	return x;
}

inline void write(int x) {
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}

//******************************************************************

int n,m,k,rev[N];
int f[N],g[N],inv[N];

// 整数操作及预处理

inline int add(int a,int b) {
	a+=b;
	if(a>=mod)return a-mod;
	return a;
}

inline int mul(int a,int b) {
	return (ll)a*b%mod;
}

inline int qpow(int a,int b) {
	int ret=1;
	while(b) {
		if(b&1) ret=mul(ret,a);
		a=mul(a,a);
		b>>=1;
	}
	return ret;
}

void init_inv() {
	inv[1]=1;
	for(int i=2; i<N; i++) 
		inv[i]=mul(mod-mod/i,inv[mod%i]);
}

// NTT核心代码

inline void init_rev(int n) {
	for(int i=0; i<n; i++) 
		rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
}

inline void NTT(int *a,int n,bool f) {
	for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int h=2; h<=n; h<<=1) {
		int w=qpow(3,(mod-1)/h);
		if(f)w=qpow(w,mod-2);
		for(int j=0; j<n; j+=h) {
			int wn=1;
			for(int k=j; k<j+(h>>1); k++) {
				int x=a[k],y=mul(wn,a[k+(h>>1)]);
				a[k]=add(x,y);
				a[k+(h>>1)]=add(x-y,mod);
				wn=mul(wn,w);
			}
		}
	}
	if(f) for(int i=0,invn=inv[n]; i<n; i++) a[i]=mul(a[i],invn);
}

// 多项式乘法

inline void cmul(int *a,int n,int *b,int m,int *c) {
	static int x[N],y[N],l;
	for(l=1; l<=(n+m-1); l<<=1);
	init_rev(l);
	memcpy(x,a,sizeof(a[0])*n);
	memcpy(y,b,sizeof(b[0])*m);
	fill(x+n,x+l,0);
	fill(y+m,y+l,0);
	NTT(x,l,0);
	NTT(y,l,0);
	for(int i=0; i<l; i++)
		c[i]=mul(x[i],y[i]);
	NTT(c,l,1);
}

// 多项式积分和微分

inline void cintegrate(int *f,int n) {
	for(int i=n; i>=1; i--) f[i]=mul(f[i-1],inv[i]);
	f[0]=0;
}

inline void cderivation(int *f,int n) {
	for(int i=1; i<n; i++) f[i-1]=mul(f[i],i);
	f[n-1]=0;
}

// 多项式乘法逆元

inline void cinv(int *a,int *b,int n) {
	static int C[N];
	if(n==0) {
		b[0]=qpow(a[0],mod-2);
		return;
	}

	cinv(a,b,n>>1);
	memcpy(C,a,sizeof(a[0])*n);
	memset(C+n,0,sizeof(a[0])*n);
	n<<=1;
	init_rev(n);
	for(int i=0; i<n; i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
	NTT(C,n,0);
	NTT(b,n,0);
	for(int i=0; i<n; i++)
		b[i]=add(mul(2,b[i])-mul(C[i],mul(b[i],b[i])),mod);
	NTT(b,n,1);
	n>>=1;
	memset(b+n,0,sizeof(b[0])*n);
}

// 多项式log

inline void cLog(int *f,int *g,int n) {
	static int D[N],A[N],m;
	memset(D,0,sizeof(D));
	memset(A,0,sizeof(A));

	for(int i=0; i<n; i++) D[i]=mul(f[i+1],(i+1));
	D[n]=0;

	for(m=1; m<=n; m<<=1);
	cinv(f,A,n);
	init_rev(m);
	NTT(A,m,0);
	NTT(D,m,0);
	for(int i=0; i<m; i++) A[i]=mul(A[i],D[i]);
	NTT(A,m,1);

	for(int i=1; i<=n; i++) g[i]=mul(A[i-1],inv[i]);
	g[0]=0;
}

// 多项式exp

inline void cexp(int *a,int *b,int n) {
	static int D[N];
	if(n==1) { b[0]=1; return; }
	cexp(a,b,n>>1);
	memset(D,0,sizeof(D));
	cLog(b,D,n);
	for(int i=0; i<n; i++)
		D[i]=add(a[i]-D[i],mod);
	D[0]=add(1,D[0]);
	n<<=1;
	init_rev(n);
	NTT(D,n,0);
	NTT(b,n,0);
	for(int i=0; i<n; i++) b[i]=mul(D[i],b[i]);
	NTT(b,n,1);
	n>>=1;
	memset(b+n,0,sizeof(b[0])*n);
}

// 多项式开根

void csqrt(int *a,int *b,int n) {
	static int C[N],D[N];
	if(n==1) {
		b[0]=sqrt(a[0]);
		return;
	}
	csqrt(a,b,n>>1);
	memset(D,0,sizeof(D));

	cinv(b,D,n);
	memcpy(C,a,sizeof(a[0])*n);
	memset(C+n,0,sizeof(C[0])*n);
	n<<=1;
	NTT(C,n,0);
	NTT(b,n,0);
	NTT(D,n,0);
	for(int i=0; i<n; i++)
		b[i]=mul(inv_2,add(b[i],mul(C[i],D[i])));
	NTT(b,n,1);
	n>>=1;
	memset(b+n,0,sizeof(b[0])*n);
}

// 多项式快速幂：g=f^k (% x^n)

inline void cpow(int *f,int *g,int n,int k) {
	static int C[N];
	memset(C,0,sizeof(C));
	cLog(f,C,m);
	for(int i=0; i<n; i++) C[i]=mul(C[i],k);
	cexp(C,g,m);
}

// 拉格朗日反演

inline int clagrange(int *f,int n,int x) {
	static int C[N],D[N];
	memset(C,0,sizeof(C));
	memset(D,0,sizeof(D));
	cinv(f,C,n);
	cpow(C,D,n,x);
	return mul(D[x-1],qpow(x,mod-2));
}

// 多项式除法

inline void cdiv(int *a,int n,int *b,int m,int *ret) {
	static int c[N],d[N],e[N],l;
	if(n<m)return;
	for(l=1; l<=n-m+1; l<<=1);
	reverse_copy(a,a+n,c);
	reverse_copy(b,b+m,d);
	for(int i=m; i<n+m+1; i++) d[i]=0; //不能用 fill(),否则 RE!!!
	memset(e,0,sizeof(e[0])*(l*2));
	cinv(d,e,l);
	cmul(e,n-m+1,c,n-m+1,d);
	reverse_copy(d,d+n-m+1,ret);
}

inline void cmod(int *a,int n,int *b,int m,int *ret) {
	static int c[N];
	cdiv(a,n,b,m,c);
	cmul(c,n-m+1,b,m,c);
	for(int i=0; i<m-1; i++) ret[i]=add(a[i]-c[i],mod);
}

// 多点求值

inline void pre(int dep,int l,int r,int *a,int b[][N]) {
	if(l==r-1) {
		b[dep][l<<1]=add(mod,-a[l]),b[dep][l<<1|1]=1;
		return;
	}
	int mid=l+r>>1;
	pre(dep+1,l,mid,a,b);
	pre(dep+1,mid,r,a,b);
	cmul(b[dep+1]+(l<<1),mid-l+1,b[dep+1]+(mid<<1),r-mid+1,b[dep]+(l<<1));
}

inline void calc(int dep,int l,int r,int *a,int b[][N]) {
	static int c[N];
	if(l==r-1)return;
	int mid=l+r>>1;
	memcpy(c,a+l,sizeof(a[0])*(r-l));
	cmod(c,r-l,b[dep+1]+(l<<1),mid-l+1,a+l);
	cmod(c,r-l,b[dep+1]+(mid<<1),r-mid+1,a+mid);
	calc(dep+1,l,mid,a,b);
	calc(dep+1,mid,r,a,b);
}

int main() {
	freopen("polynomial.in","r",stdin);
    freopen("polynomial.out","w",stdout);
	
	init_inv();
	n=read();
	k=read();
	for(int i=0; i<n; i++) f[i]=read();
	for(m=1; m<=n; m<<=1);
	csqrt(f,g,m);
	memset(f,0,sizeof(f));
	cinv(g,f,m);
	cintegrate(f,n);
	memset(g,0,sizeof(g));
	cexp(f,g,m);
	memset(f,0,sizeof(f));
	cinv(g,f,m);
	f[0]=add(f[0],1);
	memset(g,0,sizeof(g));
	cLog(f,g,m);
	g[0]=add(g[0],1);
	memset(f,0,sizeof(f));
	cpow(g,f,m,k);
	cderivation(f,n);

	for(int i=0; i<n; i++) write(f[i]),putchar(' ');
	puts("");
	
	return 0;
}
