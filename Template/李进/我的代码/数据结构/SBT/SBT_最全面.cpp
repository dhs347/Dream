struct SBT{
	int root,c[N+5][2],s[N+5],cnt,v[N+5];
	void init(){root = cnt = 0;}
	void push_up(int t){ s[t]=s[c[t][0]]+s[c[t][1]]+1; }
	int new_node(int x){ v[++cnt]=x; s[cnt]=1; c[cnt][0]=c[cnt][1]=0; return cnt; }
	void R(int &t,int p){
		int k = c[t][!p];c[t][!p]=c[k][p];c[k][p]=t; 
		s[k]=s[t]; push_up(t); t = k;
	}
	void MT(int &t,int p){
		if (s[c[c[t][p]][p]] > s[c[t][!p]]) R(t,!p); else
		if (s[c[c[t][p]][!p]] > s[c[t][!p]]) R(c[t][p],p),R(t,!p); else return;
		MT(c[t][0],0); MT(c[t][1],1); MT(t,0); MT(t,1);
	}
	void Insert(int &t,int x){
		if (! t){ t = new_node(x); return; }
		s[t]++;
		Insert(c[t][x >= v[t]],x); 
		MT(t,x >= v[t]);
	}
	int Del(int &t,int x){
		int ret;
		s[t]--;
		if (x == v[t] || c[t][x > v[t]] == 0){ 
			ret = v[t];
			if (c[t][0] && c[t][1]) v[t] = Del(c[t][0],x + 1); else t=c[t][0]+c[t][1];
			return ret;
		}
		return Del(c[t][x > v[t]],x);
	}
	int Select(int &t,int k){
		int r=s[c[t][0]]+1;
		return k==r ? v[t] : Select(c[t][k>r],k-r*(k>r));
	}
	int Rank(int &t,int x){
		if (!t) return 1;
		int r=s[c[t][0]]+1;
		return Rank(c[t][x>v[t]],x)+r*(x>v[t]);
	}
	int Pred_Succ(int p,int t,int y,int x){
		int q=(x>v[t])^p;
		return t ? Pred_Succ(p,c[t][x>v[t]],t*q+y*(!q),x) : y; 
	}
	int Find(int t,int x){
		if (t==0) return -1;
		return x==v[t] ? t : Find(c[t][x>v[t]],x);
	}
	int get_max(int t){
		for ( ; c[t][1] ; t=c[t][1]);
		return v[t];
	}
	int get_min(int t){
		for ( ; c[t][0] ; t=c[t][0]);
		return v[t];
	}
	void Print(int t){
		if (!t) return;
		Print(c[t][0]); printf("%d ",v[t]); Print(c[t][1]);
	}
};
