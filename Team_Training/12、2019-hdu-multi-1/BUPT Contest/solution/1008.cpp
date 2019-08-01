#include <bits/stdc++.h>

const int XN=(1<<18)+11,P=998244353;

int Add(int x,int const &y) {
	return (x+=y)>=P?x-P:x;
}

void AddBy(int &x,int const &y) {
	((x+=y)>=P) && (x-=P);
}

int Minus(int x,int const &y) {
	return (x-=y)<0?x+P:x;
}

int Mul(long long x,int const &y) {
	return x*y%P;
}

void MulBy(int &x,int const &y) {
	x=(long long)x*y%P;
}

int Pow(long long base,int v) {
	long long res;
	for(res=1;v;v>>=1,(base*=base)%=P)
		if(v&1)
			(res*=base)%=P;
	return res;
}

int Inverse(int x) {
	return Pow(x,P-2);
}

int Make2(int x) {
	return 1<<((32-__builtin_clz(x))+((x&(-x))!=x));
}

void NTT(int a[],int n,int op) {
	for(int i=1,j=n>>1;i<n-1;++i) {
		if(i<j)
			std::swap(a[i],a[j]);
		int k=n>>1;
		while(k<=j) {
			j-=k;
			k>>=1;
		}
		j+=k;
	}
	for(int len=2;len<=n;len<<=1) {
		int rt=Pow(3,(P-1)/len);
		for(int i=0;i<n;i+=len) {
			int w=1;
			for(int j=i;j<i+len/2;++j) {
				int u=a[j],t=Mul(a[j+len/2],w);
				a[j]=Add(u,t),a[j+len/2]=Minus(u,t);
				w=Mul(w,rt);
			}
		}
	}
	if(op==-1) {
		std::reverse(a+1,a+n);
		int in=Inverse(n);
		for(int i=0;i<n;++i)
			a[i]=Mul(a[i],in);
	}
}

void Contrb(int A[],int An,int B[],int Bn,int offset,int C[],int L,int R) {
	if((long long)An*Bn<1000000) {
		for(int i=0;i<An;++i)
			for(int j=0;j<Bn;++j) {
				int k=i+j;
				if(L<=k+offset && k+offset<=R)
					AddBy(C[k+offset],Mul(A[i],B[j]));
			}
		return;
	}
	static int a[XN],b[XN];
	int n=Make2(An+Bn-1);
	for(int i=0;i<n;++i) {
		a[i]=i<An?A[i]:0;
		b[i]=i<Bn?B[i]:0;
	}
	NTT(a,n,1);NTT(b,n,1);
	for(int i=0;i<n;++i)
		a[i]=Mul(a[i],b[i]);
	NTT(a,n,-1);
	for(int i=0;i<n;++i)
		if(L<=i+offset && i+offset<=R)
			AddBy(C[i+offset],a[i]);
}

int a[XN],b[XN],c[XN],d[XN],n,inv[XN];

void DC(int L,int R) {
	if(L==R) {
		if(L==1)
			a[L]=1;
		else
			MulBy(a[L],inv[L-1]);
		AddBy(b[L],a[L]);
		AddBy(c[L],a[L]);
		int x=Mul(L,Mul(Add(Add(b[L],c[L]),L%2==0?b[L/2]:0),inv[2]));
		for(int i=L;i<=n;i+=L)
			AddBy(d[i],x);
	} else {
		int M=(L+R)/2;
		DC(L,M);
		auto Calc=[&](int L1,int R1,int L2,int R2) {
			Contrb(a+L1,R1-L1+1,d+L2,R2-L2+1,L1+L2,a,M+1,R);
			Contrb(a+L1,R1-L1+1,b+L2,R2-L2+1,L1+L2,b,M+1,R);
			static int a2[XN];
			for(int i=L1;i<=R1;++i)
				a2[i]=i%2==0?a[i/2]:0;
			Contrb(a2+L1,R1-L1+1,c+L2,R2-L2+1,L1+L2,c,M+1,R);
		};
		if(L!=1) {
			Calc(L,M,1,R-L);
			Calc(1,R-L,L,M);
		}
		Calc(L,M,L,M);
		DC(M+1,R);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cin>>n;
	for(int i=1;i<=n;++i)
		inv[i]=Pow(i,P-2);
	DC(1,n);
	for(int i=1;i<=n;++i)
		std::cout<<a[i]<<'\n';
	return 0;
}
