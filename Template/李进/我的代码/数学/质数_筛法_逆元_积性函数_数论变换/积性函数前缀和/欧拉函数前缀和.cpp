const int _N=5000005,_M=5000000,P=5000005;

struct HT{
	int head[P],nxt[N],tot; ll v[N],e[N];
	void init(){ mem(head,0); mem(nxt,0); tot=0; }
    void I(int x,ll y,ll c){ e[++tot]=y,v[tot]=c; nxt[tot]=head[x]; head[x]=tot; }
    ll F(int x,ll y) { for (int i=head[x]; i; i=nxt[i]) if (e[i]==y) return v[i]; return -ooo; }
};

struct Euler{
	int prime[_N],tot; bool check[_N]; ll phi[_N],tmp; HT T;
	void init(){
        mem(check,0); tot=0; phi[1]=1;
        rep(i,2,_M) {
            if(!check[i]) prime[tot++]=i,phi[i]=i-1;
            rep(j,0,tot-1) {
                if ((ll)i*prime[j]>_M) break;
                check[i*prime[j]]=1;
                if (i%prime[j]==0) { phi[i*prime[j]]=phi[i]*prime[j]; break; }
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
       T.init(); phi[0]=0; rep(i,1,_M) (phi[i]+=phi[i-1])%=_p;
	}
    ll calc(ll x){
        if (x<=_M) return phi[x]; tmp=T.F(x%P,x); ll pp=x%_p;
        if (tmp!=-ooo) return tmp; ll ans=pp*(pp+1)%_p*((_p+1)/2)%_p;
        for (ll l=2,r; l<=x; l=r+1) r=x/(x/l), (ans-=(ll) ((r-l+1) % _p)*calc(x/l) %_p) %=_p;
        T.I(x%P,x,ans); return ans; //注意负数 
    }
};
