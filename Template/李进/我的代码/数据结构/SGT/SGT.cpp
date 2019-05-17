struct SGT{
	const int maxn = 1 << 16, double alpha = 0.65;
	int root,c[maxn][2],s[maxn],cnt,v[maxn],last,*temp; vector <int> V;
	void init(){root = cnt = last = 0;}
	void push_up(int t){ s[t]=s[c[t][0]]+s[c[t][1]]+1; }
	int new_node(int x){ v[++cnt]=x; s[cnt]=1; c[cnt][0]=c[cnt][1]=0; return cnt; }
	void Print(int t,int p=0){
		if (!t) return; Print(c[t][0]); 
		if (p) V.push_back(t); else printf("%d ",v[t]); 
		Print(c[t][1]);
	}
	void Build(int &t,int l,int r){
		if (!last) last=r-l+1; if (l>r) return;
		int mid=(l+r)>>1; t=V[mid];
		Build(c[t][0],l,mid-1);
		Build(c[t][1],mid+1,r);
	}
	void ReBuild(int &t){
		V.clear(); Print(t,1); Build(root,0,(int)V.size()-1);
	}
	int Ins(int &t,int x){
		if (! t) return t = new_node(x);
		s[t]++; return Ins(c[t][x >= v[t]],x); 
	}
	int Del(int &t,int x){
		int ret; s[t]--;
		if (x == v[t] || c[t][x > v[t]] == 0){ 
			ret = v[t];
			if (c[t][0] && c[t][1]) v[t] = Del(c[t][0],x + 1); else t=c[t][0]+c[t][1];
			return ret;
		}
		return Del(c[t][x > v[t]],x);
	}
	void Insert(int x){
		last++; Ins(root,x);
		
	}
	int Delete(int x){
		int ret = Del(root,x);
		if (s[root]>=alpha*last) return ret;
		last=s[root]; ReBuild(root); return ret;
	}
	int Select(int &t,int k){
		int r=s[c[t][0]]+1;
		return k==r ? v[t] : Select(c[t][k>r],k-r*(k>r));
	}
	int Rank(int &t,int x){
		if (!t) return 0;
		int r=s[c[t][0]]+1;
		return x==v[t] ? r : Rank(c[t][x>v[t]],x)+r*(x>v[t]);
	}
	int Pred_Succ(int p,int t,int y,int x){
		int q=(x>v[t])^p;
		return t ? Pred_Succ(p,c[t][x>v[t]],t*q+y*(!q),x) : y; 
	}
	int Find(int t,int x){
		if (t==0) return -1;
		return x==v[t] ? t : Find(c[t][x>v[t]],x);
	}
	int get_m(int p,int t){
		for ( ; c[t][p] ; t=c[t][p]); return v[t];
	}
};
