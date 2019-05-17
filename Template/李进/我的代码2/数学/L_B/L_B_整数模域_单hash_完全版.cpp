ll Pow(ll x,ll k,ll p) { ll ans=1; for (; k; k>>=1,(x*=x)%=_p) if (k&1) (ans*=x)%=_p; return ans; }

const int _M=100;
template <class V=ll,ll _p=(ll)1e9+7>
struct L_B{
	V base[_M+5][_M+5],a[_M+5],b[_M+5],t; int D,cnt; ll pp=13331;
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
	inline V Get_Hash_Code() const {
		V ans=D^cnt%_p;
		rep(i,0,D-1) rep(j,0,D-1) ans=((ll)ans*pp+base[i][j])%_p;
		return ans;
	}
	friend bool operator == (const L_B &_a,const L_B &_b) {
		L_B a=_a.Clone(),b=_b.Clone(); a.Normalize(),b.Normalize();
		return a.Get_Hash_Code()==b.Get_Hash_Code();
	}
	inline void Print() const { debug(D); debug(cnt); debug_arr2(base,D-1,D-1); }
};

/*

注：

线性子空间带hash处理，一个个插入d维向量，求一组基底

规范化指的是，将基底化成行阶梯最简形，对矩阵hash

1.初始化传入维数d，下标存储0..d-1

2.先规范化，然后在获取hash值

3.注意：只有规范化之后，才保证矩阵各元素非负

4.如果只需要对矩阵求行阶梯最简形，那就把行向量一个个插入，

如果插入失败，则强制插入一行0向量

5.如果hash冲突了，考虑双hash，或者采用多维张量的统一混合hash方法

*/