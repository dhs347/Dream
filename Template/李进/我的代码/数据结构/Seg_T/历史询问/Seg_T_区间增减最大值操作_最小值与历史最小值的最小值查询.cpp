struct Seg_T{
	#define lc (t<<1)
	#define rc (t<<1|1)
	#define mid ((l+r)>>1)
	int n,_mn[N<<2],mn[N<<2],cmn[N<<2],lazy[N<<2],clazy[N<<2],_lazy[N<<2],_clazy[N<<2],*a,v,L,R,opt;
	inline void clear(int t) { lazy[t] = _lazy[t] = clazy[t] = _clazy[t] = 0; }
	inline void push_up(int t) {
		_mn[t] = min(_mn[lc],_mn[rc]);
		if (mn[lc] == mn[rc]) mn[t] = mn[lc],cmn[t] = min(cmn[lc],cmn[rc]);
		else if (mn[lc] < mn[rc]) mn[t] = mn[lc],cmn[t] = min(cmn[lc],mn[rc]);
		else mn[t] = mn[rc],cmn[t] = min(cmn[rc],mn[lc]);
	}
	inline void pd(int t,int f,int opt) {
		int la = lazy[f],_la = _lazy[f],lb = clazy[f],_lb = _clazy[f];
		if (!opt) la = lb,_la = _lb;
		_lazy[t] = min(_lazy[t],lazy[t] + _la); lazy[t] += la;
		_clazy[t] = min(_clazy[t],clazy[t] + _lb); clazy[t] += lb;
		_mn[t] = min(_mn[t],mn[t] + _la);
		mn[t] += la; if (cmn[t] != oo) cmn[t] += lb;
	}
	inline void push_down(int t,int l,int r) {
		if (!lazy[t] && !clazy[t] && _lazy[t] >= 0 && _clazy[t] >= 0) return;
		if (l == r) {clear(t); return;}
		if (mn[lc] < mn[rc]) pd(lc,t,1),pd(rc,t,0);
		else if (mn[lc] > mn[rc]) pd(lc,t,0),pd(rc,t,1);
		else pd(lc,t,1),pd(rc,t,1); clear(t); 
	}
	void B(int t,int l,int r) {
		if (l == r) { mn[t] = _mn[t] = a[l]; cmn[t] = oo; clear(t); return; }
		clear(t); B(lc,l,mid); B(rc,mid+1,r); push_up(t);
	}
	void U_add(int t,int l,int r) {
		if (L <= l && r <= R) {
			lazy[t] += v; clazy[t] += v;
			_lazy[t] = min(_lazy[t],lazy[t]);
			_clazy[t] = min(_clazy[t],clazy[t]);
			mn[t] += v; if (cmn[t] != oo) cmn[t] += v;
			_mn[t] = min(_mn[t],mn[t]); return;
		}
		push_down(t,l,r);
		if (L <= mid) U_add(lc,l,mid);
		if (R > mid) U_add(rc,mid+1,r); push_up(t);
	}
	void U_max(int t,int l,int r) {
		if (v <= mn[t]) return;
		if (L <= l && r <= R && v < cmn[t]) { lazy[t] += (v - mn[t]); mn[t] = v; return; }
		push_down(t,l,r);
		if (L <= mid) U_max(lc,l,mid);
		if (R > mid) U_max(rc,mid+1,r); push_up(t);
	}
	int query(int t,int l,int r) {
		if (L <= l && r <= R) return opt == 1 ? mn[t] : _mn[t];
		int ret = oo; push_down(t,l,r);
		if (L <= mid) ret = query(lc,l,mid);
		if (R > mid) ret = min(ret,query(rc,mid+1,r)); return ret;
	}
	inline void Init(int _n,int *_a){ n=_n,a=_a,B(1,1,n); }
	inline void Update(int l,int r,int _v,int opt) { L=l,R=r,v=_v; if (!opt) U_add(1,1,n); else U_max(1,1,n); }
	inline int Query(int l,int r,int _opt) { L=l,R=r,opt=_opt; return query(1,1,n); }
}; 
