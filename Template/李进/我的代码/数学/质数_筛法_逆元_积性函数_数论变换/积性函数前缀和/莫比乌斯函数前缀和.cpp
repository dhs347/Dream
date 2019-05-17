const int _N=5000005,_M=5000000,P=5000005;

struct HT{
	int head[P],nxt[N],tot; ll v[N],e[N];
	void init(){ mem(head,0); mem(nxt,0); tot=0; }
    void I(int x,ll y,ll c){ e[++tot]=y,v[tot]=c; nxt[tot]=head[x]; head[x]=tot; }
    int F(int x,ll y) { for (int i=head[x]; i; i=nxt[i]) if (e[i]==y) return v[i]; return -oo; }
};

struct Euler{
	int prime[_N],tot; bool check[_N]; ll mu[_N],tmp; HT T;
	void init(){
        mem(check,0); tot=0; mu[1]=1;
        rep(i,2,_M) {
            if(!check[i]) prime[tot++]=i,mu[i]=-1;
            rep(j,0,tot-1) {
                if ((ll)i*prime[j]>_M) break;
                check[i*prime[j]]=1;
                if (i%prime[j]==0) { mu[i*prime[j]]=0; break; }
                mu[i*prime[j]]=-mu[i];
            }
        }
       T.init(); mu[0]=0; rep(i,1,_M) mu[i]+=mu[i-1];
	}
    ll calc(ll x){
        if (x<=_M) return mu[x]; tmp=T.F(x%P,x);
        if (tmp!=-oo) return tmp; ll ans=1;
        for (ll l=2,r; l<=x; l=r+1) r=x/(x/l),ans-=(ll)calc(x/l)*(r-l+1);
        T.I(x%P,x,ans); return ans;
    }
};
