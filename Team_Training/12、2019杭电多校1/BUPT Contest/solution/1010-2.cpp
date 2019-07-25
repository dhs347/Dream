#include <bits/stdc++.h>

const int XN=100+11,P=998244353;

void M(int &x) {
	((x>=P) && (x-=P)) || ((x<0) && (x+=P));
}

int main() {
	//freopen("input","r",stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;std::cin>>T;
	while(T--) {
    	int n;std::cin>>n;
    	static int ap[XN],bp[XN],a[XN],b[XN],c[XN][XN];
    
    	c[0][0]=1;
    	for(int i=1;i<=n;++i) {
    		c[i][0]=1;
    		for(int j=1;j<=i;++j)
    			M(c[i][j]=c[i-1][j-1]+c[i-1][j]);
    	}
    
    	auto C=[&](int n,int m) {
    		return n>=m && m>=0?c[n][m]:0;
    	};
    
        memset(bp,0,sizeof(bp));
        memset(ap,0,sizeof(ap));
        for(int i=1;i<=n;++i) {
    		std::cin>>b[i];
    		bp[b[i]]=i;
    	}
    	for(int i=1;i<=n;++i) {
    		std::cin>>a[i];
    		ap[a[i]]=i;
    	}
    
    	static int f[XN][XN][XN],g[XN][XN][XN];
    
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        
    	
    	int ghost=0;
    
    	for(int x=1;x<=n;++x) {
    		if(ap[x] && bp[x])
    			f[ap[x]][ap[x]][bp[x]]=1;
    		else if(bp[x]) {
    			for(int i=1;i<=n;++i)
    				if(!a[i])
    					f[i][i][bp[x]]=1;
    		} else if(ap[x]) {
    			for(int i=1;i<=n;++i)
    				if(!b[i])
    					f[ap[x]][ap[x]][i]=1;
    		} else 
    			ghost++;
    	}
    	for(int i=1;i<=n;++i)
    		if(!a[i])
    			for(int j=1;j<=n;++j)
    				if(!b[j])
    					f[i][i][j]=g[i][i][j]=1;//ghost;
    
    	for(int i=1;i<=n+1;++i)
    		for(int j=0;j<=n+1;++j)
    			f[i][i-1][j]=1;
    
    	for(int l=n-1;l>=1;--l)
    		for(int r=l+1;r<=n;++r)
    			for(int i=1;i<=n-(r-l);++i) 
    				if(!b[i] || !ap[b[i]] || (l<=ap[b[i]] && ap[b[i]]<=r)) {
    					int &cnt=g[l][r][i];
    					for(int k=0;k<r-l+1;++k) {
    						if(!a[l+k])
    							cnt++;
    						if(b[i+k] && !ap[b[i+k]])
    							cnt--;
    					}
    					if(b[i]) {
    						if(ap[b[i]])
    							M(f[l][r][i]+=1LL*f[l][ap[b[i]]-1][i+1]*f[ap[b[i]]+1][r][i+ap[b[i]]-l+1]%P
    									*C(g[l][r][i],g[l][ap[b[i]]-1][i+1])%P);
    						else  {
    							for(int k=l;k<=r;++k)
    								if(!a[k])
    									M(f[l][r][i]+=1LL*f[l][k-1][i+1]*f[k+1][r][i+k-l+1]%P
    											*C(g[l][r][i],g[l][k-1][i+1])%P);
    						}
    					} else {
    						for(int k=l;k<=r;++k)
    							if(!bp[a[k]] || !a[k])
    								M(f[l][r][i]+=1LL*f[l][k-1][i+1]*f[k+1][r][i+k-l+1]%P
    										*(a[k]?C(g[l][r][i],g[l][k-1][i+1])
    											:1LL*g[l][r][i]*C(g[l][r][i]-1,g[l][k-1][i+1])%P)%P);
    					}
    				}
    
    	std::cout<<f[1][n][1]<<'\n';
	}
	return 0;
}

