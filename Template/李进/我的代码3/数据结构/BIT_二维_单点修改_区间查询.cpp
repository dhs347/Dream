template <class V>
struct BIT{
	static const int N=1005,M=1005; int n,m; V t[N][M];
	void init(int _n,int _m) { mem(t,0); n=_n,m=_m;  }
	void add(int x,int y,V z) {
		for (int i=x; i<=n; i+=i&-i)
			for (int j=y; j<=m; j+=j&-j)
				t[i][j]+=z;
	}
	V ask(int x, int y){
		V ret=0;
		for (int i=x; i; i-=i&-i)
			for (int j=y; j; j-=j&-j)
				ret+=t[i][j];
		return ret;
	}
	V ask(int xa,int ya,int xb,int yb) {
		return ask(xb,yb)-ask(xb,ya-1)-ask(xa-1,yb)+ask(xa-1,ya-1);
	}
};
