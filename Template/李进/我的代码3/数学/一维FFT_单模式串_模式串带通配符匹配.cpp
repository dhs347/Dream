struct cp{ double x,y; };
inline cp operator + (cp &a,cp &b) { return cp{a.x+b.x,a.y+b.y}; }
inline cp operator - (cp &a,cp &b) { return cp{a.x-b.x,a.y-b.y}; }
inline cp operator * (cp &a,cp &b) { return cp{a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x}; }
inline cp get(double x) { return cp{cos(x),sin(x)}; }
inline ostream& operator<<(ostream &out,const cp &t) { out<<"("<<t.x<<","<<t.y<<")"; return out; }

const int _M=1<<18,_N=N;
struct FT{
	cp tmp[_M*2+5],aa[_M],bb[_M];
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
    void In(cp p[],int len,cp a[],int n) {
        rep(i,0,len) p[i]=i<n?a[i]:cp{0,0};
    }
    void Out(int a[],int n,cp p[],int len) {
        rep(i,0,n) a[i]=(int)(p[i].x+eps);
    }
    void Shift(int a[],int n,int p) { rep(i,n,n+p) a[i-n]=a[i]; }
	void Multiply(cp A[],int n,cp B[],int m,int C[],int &len,int op=0) {
	    if (op) reverse(A,A+n);
		len=1; while (len<n+m-1) len<<=1;
		In(aa,len,A,n),In(bb,len,B,m),FFT(aa,len,1),FFT(bb,len,1);
		rep(i,0,len) aa[i]=aa[i]*bb[i];
		FFT(aa,len,-1),Out(C,n+m-1,aa,len);
		if (op) Shift(C,n-1,m),len=m,reverse(A,A+n);
	}
}; 

void Build(cp A[],int n,char s[],int M,int op,int cc='a') {
	rep(i,0,n) A[i]=(s[i]=='?')?cp{0,0}:get(2*PI/M*(s[i]-cc)*op);
}

int n,m,len,tot=0,tt; char s[N],t[N]; FT T; cp A[_M],B[_M]; int C[_M]; vi ans;

int main() {
    //file_put();
    
    scanf("%s%s",s,t),n=strlen(s),m=strlen(t);
    rep(i,0,m) tot+=(t[i]!='?');
    Build(A,n,s,26,1),Build(B,m,t,26,-1);
	T.Multiply(B,m,A,n,C,len,1);
	//debug_arr(C,len-1);
    rep(i,0,n-m+1) if (C[i]>=tot) ans.pb(i);
    printf("%d\n",tt=ans.size());
    rep(i,0,tt) printf("%d\n",ans[i]);
    
    return 0;
}

