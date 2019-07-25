#include <bits/stdc++.h>

struct Istream {
	template <class T>
	Istream &operator >>(T &x) {
		static char ch;static bool neg;
		for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
		for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
		x=neg?-x:x;
		return *this;
	}
}fin;

struct Ostream {
	template <class T>
	Ostream &operator <<(T x) {
		x<0 && (putchar('-'),x=-x);
		static char stack[233];static int top;
		for(top=0;x;stack[++top]=x%10+'0',x/=10);
		for(top==0 && (stack[top=1]='0');top;putchar(stack[top--]));
		return *this;
	}

	Ostream &operator <<(char ch) {
		putchar(ch);
		return *this;
	}
}fout;

const int N=1e7,XN=N+11,P=998244353;

int Add(int x,int const &y) {
	return (x+=y)>=P?x-P:x;
}

int Minus(int x,int const &y) {
	return (x-=y)<0?x+P:x;
}

int Mul(long long x,int const &y) {
	return x*y%P;
}

int prime[XN],phi[XN],pcnt;
void Prep() {
	static bool notPrime[XN];
	phi[1]=1;
	for(int i=2;i<=N;++i) {
		if(!notPrime[i]) {
			prime[++pcnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=pcnt && i*prime[j]<=N;++j) {
			notPrime[i*prime[j]]=1;
			if(i%prime[j]==0) {
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			} else
				phi[i*prime[j]]=phi[i]*phi[prime[j]];
		}
	}
}

int Sum1(long long x) {
	return x*(x+1)/2%P;
}

int Sum2(long long x) {
	return (x*(x+1))%(6ll*P)*(2*x+1)/6%P;
}

int Calc(int a,__int128 L,__int128 R) {
	int res=0;
	for(int d=1;1LL*d*d<=a;++d)
		if(a%d==0) {
			res=Add(res,Mul((R/d-L/d)%P,phi[d]));
			if(a!=d*d)
				res=Add(res,Mul((R/(a/d)-L/(a/d))%P,phi[a/d]));
		}
	return res;
}

int main() {
	//freopen("input","r",stdin);
	Prep();
	int T;
	fin>>T;
	while(T--) {
		__int128 n;fin>>n;
		if(n<=7) {
			fout<<n<<'\n';
		} else {
			int r;for(r=1;(__int128)(r+2)*(r+2)*(r+2)-1<=n;++r);
			int Ans=Calc(r+1,(__int128)(r+1)*(r+1)*(r+1)-1,n);
			for(int T=1;T<=r;++T)
				Ans=Add(Ans,Mul(phi[T],Add(Add(Mul(3*T,Sum2(r/T)),Mul(3,Sum1(r/T))),r/T)));
			fout<<Ans<<'\n';
		}
	}
	return 0;
}

