const int _N=1e6+5,_M=1e6+5;
template <class V>
struct Tu{
	int head[_N],nxt[_M],e[_M],n,tot; V v[_N],w[_M];
	void Init(int _n) { n=_n,mem(head,0),tot=0; }
	void I(int x,int y,V _w) { e[++tot]=y,w[tot]=_w; nxt[tot]=head[x],head[x]=tot; }
};
