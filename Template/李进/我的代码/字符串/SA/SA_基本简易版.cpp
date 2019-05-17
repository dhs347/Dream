struct SA{
	int t1[N],t2[N],cc[N],x[N],sa[N],R[N],H[N],h[N],n,m; char *s;
	inline bool cmp(int *y,int a,int b,int k){
		return y[a]==y[b] && (a+k>=n ? -1:y[a+k])==(b+k>=n ? -1:y[b+k]);
	}
	inline void init_sa() {
		int *x=t1,*y=t2;
		rep(i,0,m-1) cc[i]=0;
		rep(i,0,n-1) ++cc[x[i]=s[i]];
		rep(i,1,m-1) cc[i]+=cc[i-1];
		per(i,n-1,0) sa[--cc[x[i]]]=i;
		for(int k=1,p=0; k<=n; k<<=1,p=0){
			rep(i,n-k,n-1) y[p++]=i;
			rep(i,0,n-1) if(sa[i]>=k) y[p++]=sa[i]-k;
			rep(i,0,m-1) cc[i]=0;
			rep(i,0,n-1) ++cc[x[y[i]]];
			rep(i,1,m-1) cc[i]+=cc[i-1];
			per(i,n-1,0) sa[--cc[x[y[i]]]]=y[i];
			swap(x,y),m=1,x[sa[0]]=0;
			rep(i,1,n-1) x[sa[i]]=cmp(y,sa[i],sa[i-1],k) ? m-1:m++;
			if(m>=n) break;
		}
	}
	inline void init_H(){
		rep(i,0,n-1) R[sa[i]]=i;
		int k=H[0]=s[n]=0;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}
	}
	inline void Init(char _s[],int _n,int _m='z'+1){
		s=_s,n=_n,m=_m; init_sa(); init_H();
	}
};
