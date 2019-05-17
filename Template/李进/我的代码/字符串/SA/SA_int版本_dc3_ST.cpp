struct ST{
	int n,log[N],dp[25][N]; int *a;
	int h(int x,int y) { return a[x]<=a[y] ? x:y; }
	void Init(int _n,int *_a){
		n=_n,a=_a,log[0]=-1; rep(i,1,n) log[i]=log[i>>1]+1,dp[0][i]=i;
		rep(i,1,log[n]) rep(j,1,n+1-(1<<i)) dp[i][j]=h(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
	}
	int Q(int l,int r) { int L=log[r-l+1]; return h(dp[L][l],dp[L][r+1-(1<<L)]); }
}; 

struct SA{
	int x[N],sa[4*N+5],R[N],H[N],h[N],n,m,cnt,str_cnt,num0; int *s; int num[1005],home[N]; //ST T;
	#define F(x) ((x)/3+((x)%3==1?0:tb))
	#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
	int wa[4*N+5],wb[4*N+5],wv[4*N+5],ws[4*N+5];
	int c0(int *r,int a,int b) { return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2]; }
	int c12(int k,int *r,int a,int b) {
		if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
		else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
	}
	void sort(int *r,int *a,int *b,int n,int m) {
		int i; for(i=0; i<n; i++) wv[i]=r[a[i]];
		for(i=0; i<m; i++) ws[i]=0;
		for(i=0; i<n; i++) ws[wv[i]]++;
		for(i=1; i<m; i++) ws[i]+=ws[i-1];
		for(i=n-1; i>=0; i--) b[--ws[wv[i]]]=a[i];
	}
	void dc3(int *r,int *sa,int n,int m) {
		int i,j,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p; int *rn=r+n; r[n]=r[n+1]=0;
		for(i=0; i<n; i++) if(i%3!=0) wa[tbc++]=i;
		sort(r+2,wa,wb,tbc,m);
		sort(r+1,wb,wa,tbc,m);
		sort(r,wa,wb,tbc,m);
		for(p=1,rn[F(wb[0])]=0,i=1; i<tbc; i++)
			rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
		if(p<tbc) dc3(rn,san,tbc,p);
		else for(i=0; i<tbc; i++) san[rn[i]]=i;
		for(i=0; i<tbc; i++) if(san[i]<tb) wb[ta++]=san[i]*3;
		if(n%3==1) wb[ta++]=n-1;
		sort(r,wb,wa,ta,m);
		for(i=0; i<tbc; i++) wv[wb[i]=G(san[i])]=i;
		for(i=0,j=0,p=0; i<ta && j<tbc; p++)
			sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
		for(; i<ta; p++) sa[p]=wa[i++];
		for(; j<tbc; p++) sa[p]=wb[j++];
	}
	inline void init_sa(){ s[n]=0; dc3(s,sa,n+1,m); rep(i,0,n-1) sa[i]=sa[i+1]; }
	inline void init_H(){
		rep(i,0,n-1) R[sa[i]]=i;
		int k=H[0]=0; s[n]=m-1;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}
	}
	/*inline int Q_lcp(int x,int y) {
		if (R[x]>R[y]) swap(x,y);
		return x==y ? n-x : H[T.Q(R[x]+1,R[y])];
	}*/
	/*inline int Q_lcs(int x,int y) {
		int ans=0,px=-1,py=-1;
		rep(i,0,n-1) {
			if (home[sa[i]]==x) {
				px=i; if (py!=-1) ans=max(ans,H[T.Q(py+1,i)]);
			}
			if (home[sa[i]]==y) {
				py=i; if (px!=-1) ans=max(ans,H[T.Q(px+1,i)]);
			}
		}
		return ans;
	} */
	inline void divide_group(int k,int x[]) {
		x[0]=cnt=0; rep(i,1,n-1) if (H[i]<k) x[++cnt]=i; x[++cnt]=n;
	}
	inline void count(int l,int r) {
		mem(num,0); num0=0; rep(i,l,r) num0+=!(num[home[sa[i]]]++); num0-=(num[0]>0);
	} 
	inline bool check_group(int l,int r) {
		//...
	}
	inline bool check(int ans){
		divide_group(ans,x);
		rep(i,1,cnt) if (check_group(x[i-1],x[i]-1)) return true; return false;
	}
	inline int binary(int l,int r) {
		int ans=-1,mid;
		while (l<=r) {
			mid=(l+r)>>1;
			if (check(mid)) {
				ans=mid;
				l=mid+1;
			} else r=mid-1;
		}
		return ans;
	}
	inline int Q(){
		//...
	}
	inline void Insert(int _s[],int op,int _n){
		if (n) home[n]=0,s[n++]=505+str_cnt+1; ++str_cnt;
		if (!op) rep(i,0,_n-1) home[n]=str_cnt,s[n++]=_s[i]; else
				 per(i,_n-1,0) home[n]=str_cnt,s[n++]=_s[i];
	}
	SA(){ s=new int[4*N+5]; }
	inline void Clear() { n=str_cnt=0; }
	inline void Init(int _s[]=NULL,int _n=0,int _m=505+1005){
		if (_s!=NULL) s=_s,n=_n;  m=_m;
		init_sa(); init_H(); //T.Init(n-1,H);
	}
};
