template <class V>
struct BIT{
	static const int N=1005,M=1005; int n,m;
	V t1[N][M], t2[N][M], t3[N][M], t4[N][M];
	void init(int _n,int _m) { mem(t1,0),mem(t2,0),mem(t3,0),mem(t4,0); n=_n,m=_m;  }
	void add(int x,int y,V z){
		for (int X=x; X<=n; X+=X&-X)
			for (int Y=y; Y<=m; Y+=Y&-Y) {
				t1[X][Y]+=z, t2[X][Y]+=z*x;
				t3[X][Y]+=z*y, t4[X][Y]+=z*x*y;
			}
	}
	void add(int xa,int ya,int xb,int yb,V z){
		add(xa,ya,z),add(xa,yb+1,-z);
		add(xb+1,ya,-z),add(xb+1,yb+1,z);
	}
	V ask(int x, int y){
		V res=0;
		for(int i=x; i; i-=i&-i)
			for(int j=y; j; j-=j&-j)
				res+=(x+1)*(y+1)*t1[i][j]
					-(y+1)*t2[i][j]-(x+1)*t3[i][j]+t4[i][j];
		return res;
	}
	V ask(int xa,int ya,int xb,int yb){
		return ask(xb,yb)-ask(xb,ya-1)-ask(xa-1,yb)+ask(xa-1,ya-1);
	}
};
