#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

const int maxp=26+5;
const int maxn=400000+5;

struct Suffix_Node{
	int trans[maxp],par,len;
	void Clear(){
		memset(trans,0,sizeof(trans));
		par=len=0;
	}
};

class Suffix_Automaton{
 private:
	Suffix_Node S[maxn];
	int p,np,size,crp;
 public:
 Suffix_Automaton():p(1),np(1),size(1),crp(1){};
	const void Clear(){
		for(int i=0;i<=size;++i) S[i].Clear();
		p=np=size=crp=1;
	}
	const int Match(const char ch)const{
		return S[crp].trans[ch-'a'];
	}
	const void Withdraw(const int len){
		while( crp!=0 && S[S[crp].par].len>=len ) crp=S[crp].par;
		if( crp==0 ) crp=1;
	}
	const void Transfer(const int len,const char ch){
		crp=S[crp].trans[ch-'a'];
		if( crp==0 ) crp=1;
		Withdraw(len);
	}
	const void Insert(const char ch){
		int x=ch-'a';
		np=++size;
		S[np].len=S[p].len+1;
		while( p!=0 && !S[p].trans[x] ) S[p].trans[x]=np,p=S[p].par;
		if( p==0 ) S[np].par=1;
		else{
			int q,nq;
			q=S[p].trans[x];
			if( S[q].len==S[p].len+1 ) S[np].par=q;
			else{
				nq=++size;
				S[nq]=S[q],S[nq].len=S[p].len+1;
				S[np].par=S[q].par=nq;
				while( p!=0 && S[p].trans[x]==q ) S[p].trans[x]=nq,p=S[p].par;
			}
		}
		p=np;
	}
}SAM;

string s;
ll f[maxn],p,q;

ll DP(){
	SAM.Insert(s[0]);
	f[0]=p;
	int l=1,r=0;
	for(int i=1;i<(int)s.size();++i){
		++r;
		f[i]=f[i-1]+p;
		while( ( !SAM.Match(s[i]) || r-l+1>(i+1)/2 ) && l<=r ){
			SAM.Insert(s[l++]);
			SAM.Withdraw(r-l);
		}
		SAM.Transfer(r-l+1,s[i]);
		if(l<=r){
			f[i]=min(f[i],f[i-(r-l+1)]+q);
		}
	}
	SAM.Clear();
	return f[s.size()-1];
}

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);std::cout.tie(0);
	while( cin >> s >> p >> q ){
		ll ans=DP();
		cout << ans << '\n' ;
	}
	return 0;
}
