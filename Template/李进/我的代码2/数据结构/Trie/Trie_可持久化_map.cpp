const int M=26;
template <class V>
struct Trie{
	int n,rt[N],ch[N*20][M]; char *st; V s[N*20],v;
	inline void Init() { n=0; }
	inline int new_node(int x,V _s) { s[++n]=_s,memcpy(ch[n],ch[x],sizeof(int)*M); return n; }
	void U(int &x,int y,int d) {
		x=new_node(y,s[y]); int c=st[d]-'a';
		if (st[d]) U(ch[x][c],ch[y][c],d+1); else s[x]=v;
	}
	V Q(int x,int d) {
		if (!st[d]) return s[x]; int c=st[d]-'a';
		return Q(ch[x][c],d+1);
	}
	inline void Update(int x,char *_st,V _v) { st=_st,v=_v; U(rt[x],rt[x],0); }
	inline V Query(int x,char *_st) { st=_st; return Q(rt[x],0); }
	inline void Copy(int x,int y) { rt[x]=rt[y]; }
}; 
