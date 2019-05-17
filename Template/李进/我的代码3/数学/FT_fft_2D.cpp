const int _M=2050,_N=N;
template <class V>
struct FT{
	struct cp{ double x,y; } tmp[_M*2+5]; cp aa[_M][_M],bb[_M][_M];
	friend cp operator + (cp &a,cp &b) { return cp{a.x+b.x,a.y+b.y}; }
	friend cp operator - (cp &a,cp &b) { return cp{a.x-b.x,a.y-b.y}; }
	friend cp operator * (cp &a,cp &b) { return cp{a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x}; }
	cp get(double x) { return cp{cos(x),sin(x)}; }
	void FFT(cp *a,int n,int op){
		for(int i=(n>>1),j=1;j<n;j++){
			if(i<j) swap(a[i],a[j]);
			int k; for(k=(n>>1);k&i;i^=k,k>>=1); i^=k; 
		}
		for(int m=2;m<=n;m<<=1){
			cp w=get(2*PI*op/m); tmp[0]=cp{1,0};
			for(int j=1;j<(m>>1);j++) tmp[j]=tmp[j-1]*w;
			for(int i=0;i<n;i+=m)
				for(int j=i;j<i+(m>>1);j++){
					cp u=a[j],v=a[j+(m>>1)]*tmp[j-i];
					a[j]=u+v,a[j+(m>>1)]=u-v;
				}
		}
		if(op==-1) rep(i,0,n) a[i]=cp{a[i].x/n,a[i].y/n};
	}
	void FFT(cp a[][_M],int n,int op) { rep(i,0,n) FFT(a[i],n,op); }
	template <class T>
	void Transpose(T a[][_M],int n) {
	    rep(i,0,n) rep(j,0,i) swap(a[i][j],a[j][i]);
    }
    void Reverse(V a[][_M],int n,int m) {
        rep(i,0,(n-1>>1)+1) rep(j,0,m) swap(a[i][j],a[n-1-i][j]);
        rep(i,0,n) rep(j,0,(m-1>>1)+1) swap(a[i][j],a[i][m-1-j]);
    }
    void Shift(V a[][_M],int n,int m,int p,int q) {
        rep(i,n,n+p) rep(j,m,m+q) a[i-n][j-m]=a[i][j];
    }
    void In(cp p[][_M],int len,V a[][_M],int n,int m) {
        rep(i,0,len) rep(j,0,len) p[i][j]=cp{i<n&&j<m?(double)a[i][j]:0,0};
    }
    void Out(V a[][_M],int n,int m,cp p[][_M],int len) {
        rep(i,0,n) rep(j,0,m) a[i][j]=(V)(p[i][j].x+0.5)%_p;
    }
	void Multiply(V A[][_M],int n,V B[][_M],int m,V C[][_M],int &len,int op=0) {
	    if (op) Reverse(A,n,n);
		len=1; while (len<n+m-1) len<<=1;
		In(aa,len,A,n,n),In(bb,len,B,m,m),FFT(aa,len,1),FFT(bb,len,1);
        Transpose(aa,len),Transpose(bb,len),FFT(aa,len,1),FFT(bb,len,1);
		rep(i,0,len) rep(j,0,len) aa[i][j]=aa[i][j]*bb[i][j];
		FFT(aa,len,-1),Transpose(aa,len),FFT(aa,len,-1),Out(C,len,len,aa,len);
		if (op) Shift(C,n-1,n-1,m,m),len=m,Reverse(A,n,n);
	}
}; 

inline void Random(int a[][_M],int n) {
    rep(i,0,n) rep(j,0,n) a[i][j]=rand();
}
