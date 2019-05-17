#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=3e5+10,p=998244353;
int inc(int x,int y){x+=y;return x>=p?x-p:x;}
int dec(int x,int y){x-=y;return x<0?x+p:x;}
int mul(int x,int y){return (ll)x*y%p;}
int power(int x,int y){
	int ans=1;
	for (;y;y>>=1,x=mul(x,x))
		if (y&1) ans=mul(ans,x);
	return ans;
}
int n,k,w[N],iw[N],inverse[N],a[N],ans[N];
void getinverse(){
	inverse[1]=1;
	for (int i=2;i<N;i++) inverse[i]=mul(p-p/i,inverse[p%i]);
}
void init(int n){
	w[0]=1;w[1]=power(3,(p-1)/n);
	for (int i=2;i<=n;i++) w[i]=mul(w[i-1],w[1]);
	for (int i=0;i<=n;i++) iw[i]=w[n-i];
}
void fft(int n,int *a,int *w){
	for (int i=0,j=0;i<n;i++){
		if (i>j) swap(a[i],a[j]);
		for (int k=n>>1;(j^=k)<k;k>>=1);
	}
	for (int i=2;i<=n;i<<=1){
		int m=i>>1,step=n/i;
		for (int j=0;j<n;j+=i)
		for (int k=0,pos=0;k<m;k++,pos+=step){
			int t=mul(a[j+k+m],w[pos]);
			a[j+k+m]=dec(a[j+k],t);
			a[j+k]=inc(a[j+k],t);
		}
	}
	if (w==iw) for (int i=0;i<n;i++) a[i]=mul(a[i],inverse[n]);
}
void getinv(int n,int *a,int *b){
	if (n==1) return void(b[0]=power(a[0],p-2));
	getinv((n+1)>>1,a,b);
	static int tmp[N];
	int size=1;
	while (size<n+n) size<<=1;
	init(size);
	for (int i=0;i<n;i++) tmp[i]=a[i];
	for (int i=n;i<size;i++) tmp[i]=0;
	fft(size,tmp,w);fft(size,b,w);
	for (int i=0;i<size;i++) b[i]=mul(b[i],dec(2,mul(tmp[i],b[i])));
	fft(size,b,iw);
	for (int i=n;i<size;i++) b[i]=0;
}
void getdao(int n,int *a,int *b){
	for (int i=1;i<=n;i++) b[i-1]=mul(a[i],i);
	b[n]=0;
}
void integration(int n,int *a,int *b){
	for (int i=1;i<n;i++) b[i]=mul(a[i-1],inverse[i]);
	b[0]=0;
}
void getln(int n,int *a,int *b){
	static int tmp[N],inv[N];
	int size=1;
	while (size<n+n) size<<=1;
	for (int i=0;i<size;i++) tmp[i]=inv[i]=0;
	getdao(n,a,tmp);
	getinv(n,a,inv);
	init(size);
	fft(size,tmp,w);fft(size,inv,w);
	for (int i=0;i<size;i++) tmp[i]=mul(tmp[i],inv[i]);
	fft(size,tmp,iw);
	integration(n,tmp,b);
}
void getexp(int n,int *a,int *b){
	if (n==1) return void(b[0]=1);
	getexp((n+1)>>1,a,b);
	static int ln[N];
	int size=1;
	while (size<n+n) size<<=1;
	for (int i=0;i<size;i++) ln[i]=0;
	getln(n,b,ln);
	init(size);
	for (int i=0;i<n;i++) ln[i]=dec(a[i],ln[i]);
	ln[0]=inc(ln[0],1);
	fft(size,ln,w);fft(size,b,w);
	for (int i=0;i<size;i++) b[i]=mul(b[i],ln[i]);
	fft(size,b,iw);
	for (int i=n;i<size;i++) b[i]=0;
}
void getsqrt(int n,int *a,int *b){
	if (n==1) return void(b[0]=sqrt(a[0]));
	getsqrt((n+1)>>1,a,b);
	static int tmp[N],inv[N];
	int size=1;
	while (size<n+n) size<<=1;
	for (int i=0;i<size;i++) inv[i]=0;
	getinv(n,b,inv);
	init(size);
	for (int i=0;i<n;i++) tmp[i]=a[i];
	for (int i=n;i<size;i++) tmp[i]=0;
	fft(size,tmp,w);fft(size,inv,w);fft(size,b,w);
	for (int i=0;i<size;i++) b[i]=mul(inc(mul(b[i],b[i]),tmp[i]),mul(inverse[2],inv[i]));
	fft(size,b,iw);
	for (int i=n;i<size;i++) b[i]=0;
}
int main()
{
	freopen("polynomial.in","r",stdin);
	freopen("polynomial.out","w",stdout);
	getinverse();
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	getsqrt(n,a,ans);
	for (int i=0;i<n;i++) a[i]=0;
	getinv(n,ans,a);
	for (int i=0;i<n;i++) ans[i]=0;
	integration(n,a,ans);
	for (int i=0;i<n;i++) a[i]=0;
	getexp(n,ans,a);
	for (int i=0;i<n;i++) ans[i]=0;
	getinv(n,a,ans);
	ans[0]=inc(ans[0],1);
	for (int i=0;i<n;i++) a[i]=0;
	getln(n,ans,a);
	a[0]=inc(a[0],1);
	for (int i=0;i<n;i++) ans[i]=0;
	getln(n,a,ans);
	int size=1;
	while (size<n) size<<=1;
	fft(size,ans,w);
	for (int i=0;i<size;i++) ans[i]=mul(ans[i],k);
	fft(size,ans,iw);
	for (int i=0;i<n;i++) a[i]=0;
	getexp(n,ans,a);
	for (int i=0;i<n;i++) ans[i]=0;
	getdao(n,a,ans);
	for (int i=0;i<n;i++) printf("%d ",ans[i]);
	puts("");
	return 0;
}
