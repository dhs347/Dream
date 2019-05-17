const int M=26;
template <class V>
struct Trie{
	int n,rt,ch[N*20][M]; const char *st; V s[N*20],v,v0;
	inline void Init(V _v0) { s[rt=n=1]=v0=_v0; }
	inline int new_node(V _s) { s[++n]=_s; return n; }
	int Q(int &x,int d) {
		if (!x) x=new_node(v0);
		if (!st[d]) return x; int c=st[d]-'a';
		return Q(ch[x][c],d+1);
	}
	inline V& operator[](const char *_st) { st=_st; return s[Q(rt,0)]; }
	inline V& operator[](const string &_st) { return (*this)[_st.c_str()]; }
}; 
