const int _p=(int)1e9+9, w0=115381398ll;
ll add(ll x,ll y) { x+=y; return x%_p; }
ll mul(ll x,ll y) { return x*y%_p; }
ll Pow(ll x,ll k) {
	ll ret=1;
	for (;k;k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
	return ret;
}

template <int N,int K>
struct FT{
	ll tmp[K<<1],a[N],b[N],w[K]; int t; 
    void Init(ll w0) {
        w[0]=1; rep(i,1,K) w[i]=mul(w[i-1],w0);
    } 
	void FWT(ll a[],int S,int n,int op) {
		if (n==1) return; int L=n/K;
		rep(i,0,K) FWT(a,S+L*i,n/K,op);
		rep(i,0,L) {
			rep(j,0,K) tmp[j]=0;
			rep(j,0,K) rep(k,0,K) {
				t=op*j*k%K,t<0?t+=K:0;
				tmp[j]=add(tmp[j],mul(a[S+L*k+i],w[t])); 
			}
			rep(j,0,K) a[S+L*j+i]=tmp[j];
		}
	}
	void Multiply(ll A[],ll B[],int n,ll C[]) {
	    rep(i,0,n) a[i]=A[i],b[i]=B[i];
	    FWT(a,0,n,1),FWT(b,0,n,1);
	    rep(i,0,n) a[i]=mul(a[i],b[i]);
	    FWT(a,0,n,-1); ll inv=Pow(n,_p-2);
	    rep(i,0,n) C[i]=mul(a[i],inv),C[i]<0?C[i]+=_p:0;
    }
    int get(int x,int y) {
        int ret=0,B=1;
        for (; x||y; x/=K,y/=K,B*=K) ret+=(x%K+y%K)%K*B;
        return ret;
    }
    void Multiply_B(ll A[],ll B[],int n,ll C[]) {
        rep(i,0,n) rep(j,0,n) (C[get(i,j)]+=mul(A[i],B[j]))%=_p;
        rep(i,0,n) C[i]<0?C[i]+=_p:0;
    }
};

// w0 表示单位根模域表示， 默认是3进制的， 进制要整除模数 -1

/*


1000000009

3 115381398
4 430477711
6 115381399
7 95932470
8 118835338
9 246325263
12 86475609
14 9196980
18 4138593
21 32705801
24 304035978


998244353

4 86583718
7 14553391
8 372528824
14 467509451



*/
