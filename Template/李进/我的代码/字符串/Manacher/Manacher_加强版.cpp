struct Manacher{
	char *a,b[N*2+5]; int f[N*2+5],l[N*2+5],r[N*2+5],n,m;
	inline void init(char *_a,int _n){ 
		n=_n,m=n*2,a=_a,b[0]=1; rep(i,1,n) b[2*i-1]=a[i-1],b[2*i]=0; 
		for (int i=1,p=0,q=0; i<=m; i++){
			f[i]=q>i ? min(f[2*p-i],q-i) : 1;
			for (; b[i+f[i]]==b[i-f[i]]; f[i]++);
			if (i+f[i]>q) p=i,q=i+f[i];
		}
	}
	inline void count(){
		rep(i,1,m) l[i-f[i]+1]++,l[i+1]--,r[i]++,r[i+f[i]]--;
		l[0]=r[0]=0; rep(i,1,m) l[i]+=l[i-1],r[i]+=r[i-1];
		rep(i,1,n) l[i]=l[i*2-1],r[i]=r[i*2-1];
	}
	inline void Q(){ count(); /* ... */}
};
