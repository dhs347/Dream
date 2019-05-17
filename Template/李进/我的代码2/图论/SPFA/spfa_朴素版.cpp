const int _N=1e6+5,_M=1e6+5;
template <class V>
struct Tu{
	int head[_N],nxt[_M],e[_M],n,tot; V v[_N],w[_M];
	void Init(int _n) { n=_n,mem(head,0),tot=0; }
	void I(int x,int y,V _w) { e[++tot]=y,w[tot]=_w; nxt[tot]=head[x],head[x]=tot; }
};

struct SPFA{
	int x; bool v[_N]; template <class V>
	void solve(const Tu<V> &T,int s,V dist[],V _oo=oo) {
		queue <int> Q; rep(i,1,T.n) dist[i]=_oo; 
		mem(v,0),dist[s]=0,v[s]=1,Q.push(s);
		while (!Q.empty()) {
			x=Q.front(),Q.pop(),v[x]=0;
			for (int i=T.head[x]; i; i=T.nxt[i])
				if ((ll)dist[x]+T.w[i]<dist[T.e[i]]) {
					dist[T.e[i]]=dist[x]+T.w[i];
					if (!v[T.e[i]]) Q.push(T.e[i]),v[T.e[i]]=1;
				}
		}
	}
};
