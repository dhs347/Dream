const int M=2;
template <class V,int P=31>
struct Trie{
	int n,rt,ch[N*31][M]; V s[N*31],v,v0;
	inline void Init(V _v0) { s[rt=n=1]=v0=_v0; }
	inline int new_node(V _s) { s[++n]=_s; return n; }
	int Q(int &x,int d,int delta,int y) {
		if (!x) x=new_node(v0); s[x]+=delta;
		if (d==-1) return y; int c=((v>>d)&1);
		if (delta>0 || s[ch[x][c]]) return Q(ch[x][c],d-1,delta,y*2+c);
		return Q(ch[x][c^1],d-1,delta,y*2+1-c);
	}
	int Query(int x) { v=x; return Q(rt,P-1,0,0); }
	void Del(int x) { v=x; Q(rt,P-1,-1,0); }
	void Ins(int x) { v=x; Q(rt,P-1,1,0); }
}; 
