const int _M=N,_N=N;
template <class V>
struct FT{
	struct cp{ double x,y; } tmp[_M*2+5];
	friend cp operator + (cp &a,cp &b) { return cp{a.x+b.x,a.y+b.y}; }
	friend cp operator - (cp &a,cp &b) { return cp{a.x-b.x,a.y-b.y}; }
	friend cp operator * (cp &a,cp &b) { return cp{a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x}; }
	vector <cp> aa,bb; vector <V> a[_N]; int m,_p,K;
	void Init(int _m,int _K,int p) { m=_m,K=_K,_p=p; rep(i,1,m) a[i].clear(); }
	void Insert(vector<V> C) { a[++m].swap(C); }
	void FFT(vector<cp> &a,int n,int op){
		for(int i=(n>>1),j=1;j<n;j++){
			if(i<j) swap(a[i],a[j]);
			int k; for(k=(n>>1);k&i;i^=k,k>>=1); i^=k; 
		}
		for(int m=2;m<=n;m<<=1){
			cp w=cp{cos(2*PI*op/m),sin(2*PI*op/m)};
			tmp[0]=cp{1,0};
			for(int j=1;j<(m>>1);j++) tmp[j]=tmp[j-1]*w;
			for(int i=0;i<n;i+=m)
				for(int j=i;j<i+(m>>1);j++){
					cp u=a[j],v=a[j+(m>>1)]*tmp[j-i];
					a[j]=u+v,a[j+(m>>1)]=u-v;
				}
		}
		if(op==-1) rep(i,0,n-1) a[i]=cp{a[i].x/n,a[i].y/n};
	}
	vector<V>& multiply(vector<V> &A,vector<V> &B,vector<V> *C=NULL){
		int lena=A.size(),lenb=B.size(),len=1;
		while (len<2*max(lena,lenb)) len<<=1;
		aa=vector<cp>(len),bb=vector<cp>(len);
		rep(i,0,lena-1) aa[i]=cp{(double)A[i],0};
		rep(i,0,lenb-1) bb[i]=cp{(double)B[i],0};
		FFT(aa,len,1),FFT(bb,len,1);
		rep(i,0,len-1) aa[i]=aa[i]*bb[i];
		FFT(aa,len,-1); if (!C) C=&A; (*C).clear();
		rep(i,0,min(len,K+1)-1) (*C).pb((ll)(aa[i].x+0.5)%_p);
		return *C;
	}
	vector<V>& solve(int l,int r){
		if(l==r) return a[l];
		int mid=(l+r)>>1;
		return multiply(solve(l,mid),solve(mid+1,r));
	}
	int Q(int k,int l=1,int r=0) { r=r?r:m; return solve(l,r)[k]; }
	priority_queue <pii> H;
	vector<V>& H_Merge() {
	    while (!H.empty()) H.pop();
	    rep(i,1,m) H.emplace(-a[i].size(),i);
	    while (H.size()>=2) {
	        int x=H.top().sec; H.pop();
	        int y=H.top().sec; H.pop();
	        multiply(a[x],a[y]),H.emplace(-a[x].size(),x);
        }
        return a[H.top().sec];
    }
}; 


/*

注：

1.multiply(A,B,C)是令C=A*B，如果用户不传C，则模拟A*=B，A会被修改，并返回结果

2.H_Merge()是启发式合并接口，调用后计算多项式群中所有多项式的乘积

3.Insert()支持插入一个多项式，在此之前任然需要调用Init()，设置合理的参数

4.本模板函数传参是引用传参，注意multiply，如果不要修改A，则去掉A传参的引用符号&

*/