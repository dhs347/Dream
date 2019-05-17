ll Pow(ll x,ll k,ll p) { ll ans=1; for (; k; k>>=1,(x*=x)%=_p) if (k&1) (ans*=x)%=_p; return ans; }

const int _M=100;
template <class V=ll,ll _p=(ll)1e9+7>
struct L_B{
	V base[_M+5][_M+5],a[_M+5],b[_M+5],t; int D,cnt,Hash_Cnt=2; ll PP[2]={13331,100007}; 
	inline void Init(int _D) { D=_D,mem(base,0); cnt=0; }
	inline bool I(V a[]) {
		mem(b,0);
		rep(i,0,D-1) if (a[i]) {
			if (!base[i][i]) {
				t=Pow(a[i],_p-2,_p);
				rep(j,i,D-1) base[i][j]=a[j]=(ll)a[j]*t%_p;
				cnt++; return 1;
			}
			b[i]=a[i];
			per(j,D-1,i) a[j]=(a[j]-(ll)a[i]*base[i][j]%_p)%_p;
		}
		return 0;
	}
	inline bool Insert(V _a[],V _b[]=NULL) {
		if (!_b && cnt>=D) return 0;
		memcpy(a,_a,D*sizeof(V)); bool tt=I(a);
		if (!tt && _b) memcpy(_b,b,D*sizeof(V)); return tt; 
	}
	inline void Normalize() {
		rep(i,0,D-1) if (base[i][i])
			rep(j,0,i-1) if (base[j][i]) 
				per(k,D-1,i) base[j][k]=(base[j][k]-(ll)base[i][k]*base[j][i]%_p)%_p;
		rep(i,0,D-1) rep(j,0,D-1) if (base[i][j]<0) base[i][j]+=_p;
	}
	inline L_B& Clone() const {
		L_B p; rep(i,0,D-1) rep(j,0,D-1) p.base[i][j]=base[i][j];
		p.D=D,p.cnt=cnt; return p;
	}
	friend L_B& Merge(const L_B &a,const L_B &b) {
		L_B c=a.Clone(); rep(i,0,b.D-1) c.Insert(b.base[i]); return c;
	}
	inline const V* Get_Hash_Code() const {
		V *ans=new V[Hash_Cnt]; rep(i,0,Hash_Cnt-1) ans[i]=D^cnt%_p;
		rep(i,0,D-1) rep(j,0,D-1) rep(k,0,Hash_Cnt-1) ans[k]=((ll)ans[k]*PP[k]+base[i][j])%_p;
		return ans;
	}
	friend bool operator == (const L_B &_a,const L_B &_b) {
		L_B a=_a.Clone(),b=_b.Clone(); a.Normalize(),b.Normalize();
		return a.Get_Hash_Code()==b.Get_Hash_Code();
	}
	inline void Print() const { debug(D); debug(cnt); debug_arr2(base,D-1,D-1); }
};
