#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
#include<complex>
using namespace std;
 
const double EPS=1e-9,PI=acos(-1.0);
int cmp(double k){ return k<-EPS ? -1:k>EPS ? 1:0; }
inline double sqr(double x){ return x*x; }
 
struct point {
	double x,y;
	point (){}
	point (double a,double b):x(a),y(b){}
	bool input() { return scanf("%lf%lf",&x,&y)!=EOF; }
	friend point operator +(const point &a,const point &b){
		return point(a.x+b.x,a.y+b.y);
    }  
	friend point operator -(const point &a,const point &b){
		return point(a.x-b.x,a.y-b.y);
    }
	friend bool operator ==(const point &a,const point &b){
		return cmp(a.x-b.x)==0&&cmp(a.y-b.y)==0;
    }
	friend point operator *(const point &a,const double &b){
		return point(a.x*b,a.y*b);
    }
	friend point operator*(const double &a,const point &b){
		return point(a*b.x,a*b.y);
    }
	friend point operator /(const point &a,const double &b){
		return point(a.x/b,a.y/b);
    }
	double norm() {
		return sqrt(sqr(x)+sqr(y));
    }
};
 
double cross(const point &a,const point &b){
	return a.x*b.y-a.y*b.x;
}
 
struct Circle {
	point p;
	double r;
	bool operator <(const Circle &o)const {
      if(cmp(r-o.r)!=0)return cmp(r-o.r)==-1;
      if(cmp(p.x-o.p.x)!=0)return cmp(p.x-o.p.x)==-1;
      return cmp(p.y-o.p.y)==-1;
    }
	bool operator ==(const Circle &o)const {
		return cmp(r-o.r)==0&&cmp(p.x-o.p.x)==0&&cmp(p.y-o.p.y)==0;
    }
};
 
point rotate(const point &p,double cost,double sint) {
	double x=p.x,y=p.y;
	return point(x*cost-y*sint,x*sint+y*cost);
}
 
pair<point,point> crosspoint(point ap,double ar,point bp,double br){
	double d=(ap-bp).norm();
	double cost=(ar*ar+d*d-br*br)/(2*ar*d);
	double sint=sqrt(1.-cost*cost);
	point v=(bp-ap)/(bp-ap).norm()*ar;
	return make_pair(ap+rotate(v,cost,-sint),ap+rotate(v,cost,sint));
}
 
inline pair<point,point> crosspoint(const Circle &a,const Circle &b) {	
	return crosspoint(a.p,a.r,b.p,b.r);
}
 
const int maxn=2000;
struct Node {
	point p;
	double a;
	int d;
	Node(const point &p,double a,int d):p(p),a(a),d(d){}
	bool operator <(const Node &o)const{ return a<o.a; }
};
 
double arg(point p) {
	return arg(complex<double>(p.x,p.y));
}
 
double solve(int m,Circle tc[],Circle c[]) {
	int n=0;
	sort(tc,tc+m);
	m=unique(tc,tc+m)-tc;//unique返回去重后的尾地址
	for(int i=m-1;i>=0;i--) {
		bool ok=true;
		for(int j=i+1;j<m;++j) {
			double d=(tc[i].p-tc[j].p).norm();
			if(cmp(d-abs(tc[i].r-tc[j].r))<=0) {
				ok=false;
				break;
            }
        }
		if(ok)c[n++]=tc[i];
    }
	double ans=0;
	for(int i=0;i<n;++i) {
		vector<Node> event;
		point boundary=c[i].p+point(-c[i].r,0);
		event.push_back(Node(boundary,-PI,0));
		event.push_back(Node(boundary,PI,0));
		for(int j=0;j<n;++j) {
			if(i==j)continue;
			double d=(c[i].p-c[j].p).norm();
			if(cmp(d-(c[i].r+c[j].r))<0) {
				pair<point,point> ret=crosspoint(c[i],c[j]);
				double x=arg(ret.first-c[i].p);
				double y=arg(ret.second-c[i].p);
				if(cmp(x-y)>0){
					event.push_back(Node(ret.first,x,1));
					event.push_back(Node(boundary,PI,-1));
					event.push_back(Node(boundary,-PI,1));
					event.push_back(Node(ret.second,y,-1));
                }else{
                    event.push_back(Node(ret.first,x,1));
                    event.push_back(Node(ret.second,y,-1));
                }
            }
        }
		sort(event.begin(),event.end());
		int sum=event[0].d;
		for(int j=1;j<(int)event.size();++j) {
			if(sum==0) {
				ans+=cross(event[j-1].p,event[j].p)/2.;
				double x=event[j-1].a;
				double y=event[j].a;
				double area=c[i].r*c[i].r*(y-x)/2;
				point v1=event[j-1].p-c[i].p;
				point v2=event[j].p-c[i].p;
				area-=cross(v1,v2)/2.;
				ans+=area;
            }
			sum+=event[j].d;
        }  
    }
	return ans;
}
 
Circle c[maxn],tc[maxn];
int m;

int main(){
	freopen("t.txt","r",stdin);
	
	scanf("%d",&m);
	for(int i=0;i<m;i++) tc[i].p.input(),scanf("%lf",&tc[i].r);
	printf("%.5lf\n",solve(m,tc,c)+0.00000005);
	
	return 0;
}