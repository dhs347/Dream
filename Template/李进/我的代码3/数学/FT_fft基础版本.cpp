const int _M=N,_N=N;
template <class V>
struct FT{
	struct cp{ double x,y; } tmp[_M*2+5];
	friend cp operator + (cp &a,cp &b) { return cp{a.x+b.x,a.y+b.y}; }
	friend cp operator - (cp &a,cp &b) { return cp{a.x-b.x,a.y-b.y}; }
	friend cp operator * (cp &a,cp &b) { return cp{a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x}; }
	cp get(double x) { return cp{cos(x),sin(x)}; }
	vector <cp> aa,bb;
	void FFT(vector<cp> &a,int n,int op){
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
	vector<V> multiply(vector<V> A,vector<V> B,int op=0){
	    if (op) reverse(all(A));
		int lena=A.size(),lenb=B.size(),len=1;
		while (len<lena+lenb) len<<=1;
		aa=vector<cp>(len),bb=vector<cp>(len);
		rep(i,0,lena) aa[i]=cp{(double)A[i],0};
		rep(i,0,lenb) bb[i]=cp{(double)B[i],0};
		FFT(aa,len,1),FFT(bb,len,1);
		rep(i,0,len) aa[i]=aa[i]*bb[i];
		FFT(aa,len,-1); A.clear();
        if (!op) rep(i,0,len) A.pb((ll)(aa[i].x+0.5)); else
        rep(i,lena-1,lena+lenb-2+1) A.pb((ll)(aa[i].x+0.5));
		return A;
	}
}; 
