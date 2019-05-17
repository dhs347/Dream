template <class V=ll,int M=60>
struct L_B{
	V d[M+5],p[M+5]; int cnt;
	void Init() { mem(d,0),mem(p,0),cnt=0; }
	bool Insert(V v) {
		per(i,M,0) if (v&(1ll<<i))
			if (!d[i]) { d[i]=v; break; } else v^=d[i];
		return v>0;
	}
	V Query_max(V x=0) {
		V ans=x; per(i,M,0) ans=max(ans,ans^d[i]); return ans;
	}
	V Query_min(V x=0) {
		if (!x) { rep(i,0,M) if (d[i]) return d[i]; return 0; }
		V ans=x; per(i,M,0) ans=min(ans,ans^d[i]); return ans;
	}
	void Rebuild() {
		per(i,M,0) per(j,i-1,0) if (d[i]&(1ll<<j)) d[i]^=d[j];
		rep(i,0,M) if (d[i]) p[cnt++]=d[i];
	}
	V Query_kth(V k) {
		if (k>=(1ll<<cnt)) return -1; V ans=0;
		per(i,M,0) if (k&(1ll<<i)) ans^=p[i]; return ans;
	}
	L_B& Clone() {
		L_B C; rep(i,0,M) C.d[i]=d[i],C.p[i]=p[i]; C.cnt=cnt; return C;
	}
	friend L_B& Merge(const L_B &A,const L_B &B) {
		L_B C=A.Clone(); per(i,M,0) if (B.d[i]) C.Insert(B.d[i]); return C;
	}
}; 
