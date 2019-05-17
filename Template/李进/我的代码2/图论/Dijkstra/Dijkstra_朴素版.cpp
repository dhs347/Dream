const int _N=1e6+5,_M=1e6+5;
template <class V>
struct Tu{
	int head[_N],nxt[_M],e[_M],n,tot; V v[_N],w[_M];
	void Init(int _n) { n=_n,mem(head,0),tot=0; }
	void I(int x,int y,V _w) { e[++tot]=y,w[tot]=_w; nxt[tot]=head[x],head[x]=tot; }
};

template <class V>
struct Dijkstra{
	struct node{ int id; V d; }; int x; bool v[_N]; V d;
	friend bool operator < (const node &p,const node &q) { return p.d>q.d; }
	void solve(const Tu<V> &T,int s,V dist[],V _oo=oo) {
		priority_queue <node> Q; rep(i,1,T.n) dist[i]=_oo; 
		mem(v,0),dist[s]=0,Q.push(node{s,0});
		while (!Q.empty()) {
			x=Q.top().id,d=Q.top().d,Q.pop();
			if (v[x] || dist[x]!=d) continue; v[x]=1;
			for (int i=T.head[x]; i; i=T.nxt[i])
				if ((ll)dist[x]+T.w[i]<dist[T.e[i]]) {
					dist[T.e[i]]=dist[x]+T.w[i];
					Q.push(node{T.e[i],dist[T.e[i]]});
				}
		}
	}
};
