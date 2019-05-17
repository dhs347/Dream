struct cp{ double x,y; };
inline cp operator + (cp &a,cp &b) { return cp{a.x+b.x,a.y+b.y}; }
inline cp operator - (cp &a,cp &b) { return cp{a.x-b.x,a.y-b.y}; }
inline cp operator * (cp &a,cp &b) { return cp{a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x}; }
inline cp get(double x) { return cp{cos(x),sin(x)}; }
inline ostream& operator<<(ostream &out,const cp &t) { out<<"("<<t.x<<","<<t.y<<")"; return out; }

const int _M=2048,_N=N;
template <class V>
struct FT{
	cp tmp[_M*2+5],aa[_M][_M],bb[_M][_M];
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
    void Shift(int a[][_M],int n,int m,int p,int q) {
        rep(i,n,n+p) rep(j,m,m+q) a[i-n][j-m]=a[i][j];
    }
    void In(cp p[][_M],int len,V a[][_M],int n,int m) {
        rep(i,0,len) rep(j,0,len) p[i][j]=i<n&&j<m?a[i][j]:cp{0,0};
    }
    void Out(int a[][_M],int n,int m,cp p[][_M],int len) {
        rep(i,0,n) rep(j,0,m) a[i][j]=(int)(p[i][j].x+eps);
    }
	void Multiply(V A[][_M],int n,V B[][_M],int m,int C[][_M],int &len,int op=0) {
	    if (op) Reverse(A,n,n);
		len=1; while (len<n+m-1) len<<=1;
		In(aa,len,A,n,n),In(bb,len,B,m,m),FFT(aa,len,1),FFT(bb,len,1);
        Transpose(aa,len),Transpose(bb,len),FFT(aa,len,1),FFT(bb,len,1);
		rep(i,0,len) rep(j,0,len) aa[i][j]=aa[i][j]*bb[i][j];
		FFT(aa,len,-1),Transpose(aa,len),FFT(aa,len,-1),Out(C,len,len,aa,len);
		if (op) Shift(C,n-1,n-1,m,m),len=m,Reverse(A,n,n);
	}
}; 

void Build(cp A[][_M],int n,int m,char s[][405],int M,int op,int cc='a') {
	rep(i,0,n) rep(j,0,m) A[i][j]=(s[i][j]=='?')?cp{0,0}:get(2*PI/M*(s[i][j]-cc)*op);
}

int n1,n2,m1,m2,nn,mm,len,tot=0; char s[405][405],t[405][405]; FT<cp> T; cp A[_M][_M],B[_M][_M]; int C[_M][_M];

int main() {
    //file_put();
    
    scanf("%d%d",&n1,&m1);
    rep(i,0,n1) scanf("%s",s[i]);
    scanf("%d%d",&n2,&m2),nn=n1+n2,mm=m1+m2;
    rep(i,0,n2) scanf("%s",t[i]);
    rep(i,0,n2) rep(j,0,m2) tot+=(t[i][j]!='?');
    Build(A,n1,m1,s,26,1),Build(B,n2,m2,t,26,-1);
    rep(i,0,nn) rep(j,0,mm) {
        if (i<n1 && j<m1) continue;
        A[i][j]=A[i%n1][j%m1];
    }
    //debug_arr2(A,nn-1,mm-1);
    //debug_arr2(B,n2-1,m2-1);
	T.Multiply(B,max(n2,m2),A,max(nn,mm),C,len,1);
    //debug_arr2(C,len-1,len-1);
    rep(i,0,n1) {
        rep(j,0,m1) printf("%c","01"[C[i][j]>=tot]);
        printf("\n");
    }
    
    return 0;
}
