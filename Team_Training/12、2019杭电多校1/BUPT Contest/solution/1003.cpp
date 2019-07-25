#include <bits/stdc++.h>

template <class T>
bool Reduce(T &a,T const &b) {
	return a>b?a=b,1:0;
}

const int XN=1e4+11;
const long long INF=1e18;

std::vector<long long> Merge(std::vector<long long> const &a,std::vector<long long> const &b) {	
	std::vector<long long> c(a.size()+b.size()-1,INF);
	for(size_t i=0;i<a.size();++i)
		for(size_t j=0;j<b.size();++j)
			Reduce(c[i+j],a[i]+b[j]);
	return c;
}

std::vector<long long> Go(std::vector<std::pair<int,int>> const &a,int dest) {
	std::vector<long long> c(a.size(),INF),t(a.size(),INF);
	c[0]=dest==-1?0:abs(dest-a[0].first);
	t[0]=0;
	for(int i=1;i<(int)a.size();++i) {
		int len=abs(a[i].first-a[i-1].first);
		for(int j=0;j<i;++j)
			t[j]+=len;
		for(int j=i;j>=1;--j)
			Reduce(t[j],t[j-1]+a[i].second);
		for(int j=0;j<=i;++j)
			Reduce(c[j],t[j]+(dest==-1?0:abs(dest-a[i].first)));
	}
	return c;
}

int main() {
//	freopen("in","r",stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;std::cin>>T;
	while(T--) {
		//std::cerr<<T<<':';
		int n,m,k;std::cin>>n>>m>>k;
		static std::tuple<int,int,int> p[XN]; 
		std::vector<int> x{1};
		for(int i=1;i<=k;++i) {
			std::cin>>std::get<0>(p[i])>>std::get<1>(p[i])>>std::get<2>(p[i]);
			x.push_back(std::get<0>(p[i]));
		}
		std::sort(x.begin(),x.end());
		x.erase(std::unique(x.begin(),x.end()),x.end());
		static std::vector<std::pair<int,int>> a[XN];
		static long long Ans[XN];
		for(size_t i=0;i<x.size();++i)
			a[i].clear();
		for(int i=1;i<=k;++i) {
			a[std::lower_bound(x.begin(),x.end(),std::get<0>(p[i]))-x.begin()].push_back({std::get<1>(p[i]),
					std::get<2>(p[i])});
			Ans[i]=INF;
		}
		for(size_t i=0;i<x.size();++i)
			std::sort(a[i].begin(),a[i].end());
		static std::vector<long long> f[2];
		
		auto t=a[0];
		t.insert(t.begin(),{1,0});
		f[0]=Go(t,(m+1)/2);
		auto g=Go(t,-1);
		for(size_t i=0;i<t.size();++i)
			Reduce(Ans[i],g[i]);

		for(int i=1;i<(int)x.size();++i) {
			auto sp=std::lower_bound(a[i].begin(),a[i].end(),std::make_pair((m+1)/2,0));
			std::vector<std::pair<int,int>> t0(a[i].begin(),sp),t1(sp,a[i].end());
			t0.push_back({(m+1)/2,0});std::reverse(t0.begin(),t0.end());
			t1.insert(t1.begin(),{(m+1)/2,0});

			auto f0=Go(t0,(m+1)/2),f1=Go(t1,(m+1)/2),g0=Go(t0,-1),g1=Go(t1,-1);

			g0=Merge(f1,g0);g1=Merge(f0,g1);

			assert(g0.size()==g1.size());

			std::vector<long long> g(g0.size());
			for(size_t i=0;i<g.size();++i)
				g[i]=std::min(g0[i],g1[i]);
			g=Merge(f[(i-1)&1],g);

			f[i&1]=Merge(f[(i-1)&1],Merge(f0,f1));
			for(size_t j=0;j<g.size();++j) {
				Reduce(Ans[j],g[j]+=x[i]-x[i-1]);
				f[i&1][j]+=x[i]-x[i-1];
			}
		}

		for(int i=1;i<=k;++i)
			std::cout<<Ans[i]<<(i==k?'\n':' ');
	}
	return 0;
}
