ll Pow(ll x,ll a){
	if (a==0) return 1;
	if (a==1) return x;
	ll y=Pow(x,a>>1); (y*=y)%=_p;
	if (a&1) (y*=x)%=_p; return y;
}

const int _N=5000005,_M=5000000,P=5000005;

struct HT{
	int head[P],nxt[N],tot; ll v[N],e[N];
	void init(){ mem(head,0); mem(nxt,0); tot=0; }
    void I(int x,ll y,ll c){ e[++tot]=y,v[tot]=c; nxt[tot]=head[x]; head[x]=tot; }
    ll F(int x,ll y) { for (int i=head[x]; i; i=nxt[i]) if (e[i]==y) return v[i]; return -ooo; }
};

struct Euler{
	int prime[_N],tot; bool check[_N]; ll f[_N],tmp; HT T;
	void init(){
        mem(check,0); tot=0; f[1]=1;
        rep(i,2,_M) {
            if(!check[i]) prime[tot++]=i,f[i]=i-1;
            rep(j,0,tot-1) {
                if ((ll)i*prime[j]>_M) break;
                check[i*prime[j]]=1;
                if (i%prime[j]==0) { f[i*prime[j]]=f[i]*prime[j]; break; }
                f[i*prime[j]]=f[i]*(prime[j]-1);
            }
        }
		rep(i,1,_M) (f[i]*=(1 /* ... */))%=_p;
        T.init(); f[0]=0; rep(i,1,_M) (f[i]+=f[i-1])%=_p;
	}
	inline ll H(ll x){ x%=_p; return 1 /* ... */; }
	inline ll G(ll x) { x%=_p; return 1 /* ... */; }
    ll F(ll x){
        if (x<=_M) return f[x]; tmp=T.F(x%P,x); ll g1_inv=1;
        if (tmp!=-ooo) return tmp; ll ans=H(x);
        for (ll l=2,r; l<=x; l=r+1) r=x/(x/l), (ans-=1 /* ... */ ) %=_p;
		//(ans*=g1_inv)%=_p;    //注意g(1)的逆元
        T.I(x%P,x,ans); return ans; 
    }
    ll query(ll n){
		ll ans=0,t;
		for (ll l=1,r; l<=n; l=r+1) r=n/(n/l), t=n/l%_p, (ans+=1 /* ... */ )%=_p;
		return (ans+_p)%_p; 
	}
};
