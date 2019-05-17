template <class V>
struct BIT{
	static const int N=1005,M=1005; int n,m; V t[N][M];
	void init(int _n,int _m) { mem(t,0); n=_n,m=_m;  }
	void add(int x,int y,V z) {
		for (int i=x; i<=n; i+=i&-i)
			for (int j=y; j<=m; j+=j&-j)
				t[i][j]+=z;
	}
	void add(int xa,int ya,int xb,int yb,V z) {
		add(xa,ya,z),add(xa,yb+1,-z),add(xb+1,ya,-z),add(xb+1,yb+1,z);
	}
	V ask(int x, int y){
		V ret=0;
		for (int i=x; i; i-=i&-i)
			for (int j=y; j; j-=j&-j)
				ret+=t[i][j];
		return ret;
	}
};
