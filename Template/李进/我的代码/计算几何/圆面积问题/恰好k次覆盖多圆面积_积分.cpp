#include<bits/stdc++.h> 
using namespace std;
#define For(i,n) for(int i=1;i<=n;i++)
#define Fork(i,k,n) for(int i=k;i<=n;i++)
#define ForkD(i,k,n) for(int i=n;i>=k;i--)
#define Rep(i,n) for(int i=0;i<n;i++)
#define ForD(i,n) for(int i=n;i;i--)
#define RepD(i,n) for(int i=n;i>=0;i--)
#define Forp(x) for(int p=pre[x];p;p=next[p])
#define Forpiter(x) for(int &p=iter[x];p;p=next[p])  
#define Lson (o<<1)
#define Rson ((o<<1)+1)
#define MEM(a) memset(a,0,sizeof(a));
#define MEMI(a) memset(a,0x3f,sizeof(a));
#define MEMi(a) memset(a,128,sizeof(a));
#define MEMx(a,b) memset(a,b,sizeof(a));
#define INF (0x3f3f3f3f)
#define F (1000000007)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define vi vector<int> 
#define pi pair<int,int>
#define SI(a) ((a).size())
#define Pr(kcase,ans) printf("Case #%d: %lld\n",kcase,ans);
#define PRi(a,n) For(i,n-1) cout<<a[i]<<' '; cout<<a[n]<<endl;
#define PRi2D(a,n,m) For(i,n) { \
                        For(j,m-1) cout<<a[i][j]<<' ';\
                        cout<<a[i][m]<<endl; \
                        } 
#pragma comment(linker, "/STACK:102400000,102400000")
#define ALL(x) (x).begin(),(x).end()
#define gmax(a,b) a=max(a,b);
#define gmin(a,b) a=min(a,b);
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
ll mul(ll a,ll b){return (a*b)%F;}
ll add(ll a,ll b){return (a+b)%F;}
ll sub(ll a,ll b){return ((a-b)%F+F)%F;}
void upd(ll &a,ll b){a=(a%F+b%F)%F;}
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar();}
    return x*f;
} 
ll sqr(ll a){return a*a;}
ld sqr(ld a){return a*a;}
double sqr(double a){return a*a;}
const double eps=1e-8;
int dcmp(double x) {
    if (fabs(x)<eps) return 0; else return x<0 ? -1 : 1; 
}
ld PI = 3.141592653589793238462643383;
class P{
public:
    double x,y;
    P(double x=0,double y=0):x(x),y(y){}
    friend ld dis2(P A,P B){return sqr(A.x-B.x)+sqr(A.y-B.y);   }
    friend ld Dot(P A,P B) {return A.x*B.x+A.y*B.y; }
    friend ld Length(P A) {return sqrt(Dot(A,A)); }
    friend ld Angle(P A,P B) {
        if (dcmp(Dot(A,A))==0||dcmp(Dot(B,B))==0||dcmp(Dot(A-B,A-B))==0) return 0;
        return acos(max((ld)-1.0, min((ld)1.0, Dot(A,B) / Length(A) / Length(B) )) ); 
    }

    friend P operator- (P A,P B) { return P(A.x-B.x,A.y-B.y); }
    friend P operator+ (P A,P B) { return P(A.x+B.x,A.y+B.y); }
    friend P operator* (P A,double p) { return P(A.x*p,A.y*p); }
    friend P operator/ (P A,double p) { return P(A.x/p,A.y/p); }
    friend bool operator< (const P& a,const P& b) {return dcmp(a.x-b.x)<0 ||(dcmp(a.x-b.x)==0&& dcmp(a.y-b.y)<0 );}

}; 
P read_point() {
    P a;
    scanf("%lf%lf",&a.x,&a.y);
    return a;   
} 
bool operator==(const P& a,const P& b) {
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y) == 0;
} 
typedef P V;

double Cross(V A,V B) {return A.x*B.y - A.y*B.x;}
double Area2(P A,P B,P C) {return Cross(B-A,C-A);}
V Rotate(V A,double rad) {
    return V(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
} 
// A 不是 0向量 
V Normal(V A) { 
    double L = Length(A);
    return V(-A.y/L , A.x/L); 
}

namespace complex_G{
    typedef complex<double> Point;
    //real(p):实部 imag(p):虚部 conj(p):共轭 
    typedef Point Vector;
    double Dot(Vector A,Vector B) {return real(conj(A)*B); }
    double Cross(Vector A,Vector B) {return imag(conj(A)*B); }
    Vector Rotate(Vector A,double rad) {return A*exp(Point(0,rad)); }
}
//Cross(v,w)==0(平行)时,不能调这个函数 
P GetLineIntersection(P p,V v,P Q,V w){
    V u = p-Q;
    double t = Cross(w,u)/Cross(v,w);
    return p+v*t;
}
P GetLineIntersectionB(P p,V v,P Q,V w){
    return GetLineIntersection(p,v-p,Q,w-Q);
}

double DistanceToLine(P p,P A,P B) {
    V v1 = B-A, v2 = p-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double DistanceToSegment(P p,P A,P B) {
    if (A==B) return Length(p-A);
    V v1 = B-A, v2 = p-A, v3 = p - B;
    if (dcmp(Dot(v1,v2))<0) return Length(v2);
    else if (dcmp(Dot(v1,v3))>0 ) return Length(v3);
    else return fabs(Cross(v1,v2) ) / Length(v1);
}
P GetLineProjection(P p,P A,P B) {
    V v=B-A;
    return A+v*(Dot(v,p-A)/Dot(v,v));
}
//规范相交-线段相交且交点不在端点 
bool SegmentProperIntersection(P a1,P a2,P b1,P b2) { 
    double  c1 = Cross(a2-a1,b1-a1) , c2 = Cross(a2-a1,b2-a1),
            c3 = Cross(b2-b1,a1-b1) , c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
//点在线段上（不包含端点） 
bool OnSegment(P p,P a1,P a2) {
    return dcmp(Cross(a1-p,a2-p)) == 0 && dcmp(Dot(a1-p,a2-p))<0;
}
double PolygonArea(P *p,int n) {
    double area=0;
    For(i,n-2) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
} 
/*欧拉公式： V+F-E=2 
V-点数 F面数 E边数 */
struct C{
    P c;
    double r,x,y;
    C(){}
    C(P c,double r=0):c(c),r(r),x(c.x),y(c.y){}
    P point(double a) {
        return P(c.x+cos(a)*r,c.y+sin(a)*r);
    }

};

struct Line{
    P p;
    V v;
    double ang;
    Line(){}
    Line(P p,V v):p(p),v(v) {ang=atan2(v.y,v.x); }
    bool operator<(const Line & L) const {
        return ang<L.ang;
    }
    P point(double a) {
        return p+v*a;
    }
};
int getLineCircleIntersection(Line L,C cir,double &t1,double &t2,vector<P> & sol) {
    if (dcmp(DistanceToLine(cir.c,L.p,L.p+L.v)-cir.r)==0) {
        P A=GetLineProjection(cir.c,L.p,L.p+L.v);
        sol.pb(A); 
        t1 = (A-L.p).x / L.v.x;  
        return 1;
    }

    double a = L.v.x, b = L.p.x - cir.c.x, c = L.v.y, d= L.p.y - cir.c.y;
    double e = a*a+c*c, f = 2*(a*b + c*d), g = b*b+d*d-cir.r*cir.r;
    double delta = f*f - 4*e*g;
    if (dcmp(delta)<0) return 0;
    else if (dcmp(delta)==0) {
        t1 = t2 = -f / (2*e); sol.pb(L.point(t1));
        return 1;
    } 
    t1 = (-f - sqrt(delta)) / (2*e); sol.pb(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2*e); sol.pb(L.point(t2));
    return 2;
}
double angle(V v) {return atan2(v.y,v.x);}
int getCircleCircleIntersection(C C1,C C2,vector<P>& sol) {
    double d = Length(C1.c-C2.c);
    if (dcmp(d)==0) {
        if (dcmp(C1.r - C2.r)==0) return -1; //2圆重合 
        return 0;
    }
    if (dcmp(C1.r+C2.r-d)<0) return 0;
    if (dcmp(fabs(C1.r-C2.r)-d)>0) return 0;

    double a = angle(C2.c-C1.c);
    double da = acos((C1.r*C1.r+d*d - C2.r*C2.r)/ (2*C1.r*d));
    P p1 = C1.point(a-da), p2 = C1.point(a+da);
    sol.pb(p1);
    if (p1==p2) return 1;
    sol.pb(p2);
    return 2; 
}
// Tangents-切线 
int getTangents(P p,C c,V* v) {
    V u= c.c-p;
    double dist = Length(u);
    if (dist<c.r) return 0;
    else if (dcmp(dist-c.r)==0) {
        v[0]=Rotate(u,PI/2);
        return 1;
    } else {
        double ang = asin(c.r / dist);
        v[0]=Rotate(u,-ang);
        v[1]=Rotate(u,ang);
        return 2;
    }       
}
int getTangentsPoint(P p,C c,P *point) {
    V u= c.c-p;
    double dist = Length(u);
    if (dist<c.r) return 0;
    else if (dcmp(dist-c.r)==0) {
        point[0]=p;
        return 1;
    } else {
        V v[2];
        double ang = asin(c.r / dist);
        v[0]=Rotate(u,-ang);point[0]=GetLineProjection(c.c,p,p+v[0]);
        v[1]=Rotate(u,ang); point[1]=GetLineProjection(c.c,p,p+v[1]);
        return 2;
    }
}
//这个函数假设整数坐标和整数半径
//double时要把int改成double 
int getTangents(C A,C B,P* a,P* b) {
    int cnt=0;
    if (A.r<B.r) {swap(A,B),swap(a,b);}
    int d2 = (A.c.x-B.c.x)*(A.c.x-B.c.x) + (A.c.y-B.c.y)*(A.c.y-B.c.y);
    int rdiff = A.r-B.r;
    int rsum = A.r+B.r;
    if (d2<rdiff*rdiff) return 0;
    double base = atan2(B.y-A.y,B.x-A.x);
    if (d2==0 && A.r == B.r) return -1;
    if (d2 == rdiff*rdiff) {
        a[cnt] = A.point(base); b[cnt] = B.point(base); ++cnt;
        return 1;
    }
    double ang = acos((A.r-B.r)/sqrt(d2));
    a[cnt] = A.point(base+ang); b[cnt] = B.point(base+ang); ++cnt;
    a[cnt] = A.point(base-ang); b[cnt] = B.point(base-ang); ++cnt;
    if (d2==rsum*rsum) {
        a[cnt] = A.point(base); b[cnt] = B.point(PI+base); ++cnt;
    }
    else if (d2>rsum*rsum) {
        double ang = acos((A.r+B.r)/sqrt(d2));
        a[cnt] = A.point(base+ang); b[cnt] = B.point(PI+base+ang); ++cnt;
        a[cnt] = A.point(base-ang); b[cnt] = B.point(PI+base-ang); ++cnt;
    }
    return cnt; 
}
//Circumscribed-外接 
C CircumscribedCircle(P p1,P p2,P p3) {
    double Bx = p2.x-p1.x, By= p2.y-p1.y;
    double Cx = p3.x-p1.x, Cy= p3.y-p1.y;
    double D = 2*(Bx*Cy-By*Cx);
    double cx = (Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D + p1.x;
    double cy = (Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D + p1.y;
    P p =P(cx,cy);
    return C(p,Length(p1-p));
}
//Inscribed-内接 
C InscribedCircle(P p1,P p2,P p3) {
    double a = Length(p2-p3);
    double b = Length(p3-p1);
    double c = Length(p1-p2);
    P p = (p1*a+p2*b+p3*c)/(a+b+c);
    return C(p,DistanceToLine(p,p1,p2));
}
double torad(double deg) {
    return deg/180*acos(-1);
}
//把 角度+-pi 转换到 [0,pi) 上 
double radToPositive(double rad) {
    if (dcmp(rad)<0) rad=ceil(-rad/PI)*PI+rad;
    if (dcmp(rad-PI)>=0) rad-=floor(rad/PI)*PI; 
    return rad;
} 
double todeg(double rad) {
    return rad*180/acos(-1);
}

//(R,lat,lng)->(x,y,z)
void get_coord(double R,double lat,double lng,double &x,double &y,double &z) {
    lat=torad(lat);
    lng=torad(lng);
    x=R*cos(lat)*cos(lng);
    y=R*cos(lat)*sin(lng);
    z=R*sin(lat);
}
void print(double a) {
    printf("%.6lf",a); 
}
void print(P p) {
    printf("(%.6lf,%.6lf)",p.x,p.y);
}
template<class T>
void print(vector<T> v) {
    sort(v.begin(),v.end());
    putchar('[');
    int n=v.size();
    Rep(i,n) {
        print(v[i]);
        if (i<n-1) putchar(','); 
    }
    puts("]");
}
// 把直线沿v平移
// Translation-平移 
Line LineTranslation(Line l,V v) {
    l.p=l.p+v;
    return l;
}
void CircleThroughAPointAndTangentToALineWithRadius(P p,Line l,double r,vector<P>& sol) {
    V e=Normal(l.v);
    Line l1=LineTranslation(l,e*r),l2=LineTranslation(l,e*(-r));
    double t1,t2;
    getLineCircleIntersection(l1,C(p,r),t1,t2,sol);
    getLineCircleIntersection(l2,C(p,r),t1,t2,sol);
}
void CircleTangentToTwoLinesWithRadius(Line l1,Line l2,double r,vector<P>& sol) {
    V e1=Normal(l1.v),e2=Normal(l2.v);
    Line L1[2]={LineTranslation(l1,e1*r),LineTranslation(l1,e1*(-r))},
         L2[2]={LineTranslation(l2,e2*r),LineTranslation(l2,e2*(-r))};
    Rep(i,2) Rep(j,2) sol.pb(GetLineIntersection(L1[i].p,L1[i].v,L2[j].p,L2[j].v));
}
void CircleTangentToTwoDisjointCirclesWithRadius(C c1,C c2,double r,vector<P>& sol) {
    c1.r+=r; c2.r+=r;
    getCircleCircleIntersection(c1,c2,sol);
}
//确定4个点能否组成凸多边形，并按顺序（不一定是逆时针）返回 
bool ConvexPolygon(P &A,P &B,P &C,P &D) {
    if (SegmentProperIntersection(A,C,B,D)) return 1;
    swap(B,C);
    if (SegmentProperIntersection(A,C,B,D)) return 1;
    swap(D,C);
    if (SegmentProperIntersection(A,C,B,D)) return 1;
    return 0;
}
bool IsParallel(P A,P B,P C,P D) {
    return dcmp(Cross(B-A,D-C))==0;
}
bool IsPerpendicular(V A,V B) {
    return dcmp(Dot(A,B))==0;
}
//先调用ConvexPolygon 求凸包并确认是否是四边形
// Trapezium-梯形 Rhombus-菱形  
bool IsTrapezium(P A,P B,P C,P D){
    return IsParallel(A,B,C,D)^IsParallel(B,C,A,D);
}
bool IsParallelogram(P A,P B,P C,P D) {
    return IsParallel(A,B,C,D)&&IsParallel(B,C,A,D);
}
bool IsRhombus(P A,P B,P C,P D) {
    return IsParallelogram(A,B,C,D)&&dcmp(Length(B-A)-Length(C-B))==0;
}
bool IsRectangle(P A,P B,P C,P D) {
    return IsParallelogram(A,B,C,D)&&IsPerpendicular(B-A,D-A);
}
bool IsSquare(P A,P B,P C,P D) {
    return IsParallelogram(A,B,C,D)&&IsPerpendicular(B-A,D-A)&&dcmp(Length(B-A)-Length(C-B))==0;
}

//chord-弦 arc-弧 
double ArcDis(double chord,double r) {
    return 2*asin(chord/2/r)*r;
} 
typedef vector<P> Polygon ;
int isPointInPolygon(P p,Polygon poly) {
    int wn=0;
    int n=poly.size();
    Rep(i,n) {
        if (OnSegment(p,poly[i],poly[(i+1)%n])) return -1; //edge
        int k=dcmp(Cross(poly[(i+1)%n]-poly[i],p-poly[i]));
        int d1 = dcmp(poly[i].y-p.y);
        int d2 = dcmp(poly[(i+1)%n].y-p.y);
        if ( k > 0 && d1 <= 0 && d2 > 0 ) wn++;
        if ( k < 0 && d2 <= 0 && d1 > 0 ) wn--;
    }
    if (wn!=0) return 1; //inside
    return 0; //outside
}

int ConvexHull(P *p,int n,P *ch) {
    sort(p,p+n);
    int m=0;
    Rep(i,n) {
        while(m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++]=p[i];
    }
    int k=m;
    RepD(i,n-2) {
        while(m>k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++]=p[i];
    }
    if ( n > 1 ) m--;
    return m;
}
//把两点式转为一般式 ax+by+c=0 
void Two_pointFormToGeneralForm(P A,P B,double &a,double &b,double &c){
    a = A.y - B.y;
    b = B.x - A.x;
    c = Cross(A,B);
}
//有向直线A->B 切割多边行poly 可能返回单点线段 O(n)
Polygon CutPolygon(Polygon poly,P A,P B){
    Polygon newpoly;
    int n=poly.size();
    Rep(i,n) {
        P C = poly[i];
        P D = poly[(i+1)%n];
        if (dcmp(Cross(B-A,C-A))>=0)  newpoly.pb(C);
        if (dcmp(Cross(B-A,C-D))) {
            P ip = GetLineIntersection(A,B-A,C,D-C);
            if (OnSegment(ip,C,D)) newpoly.pb(ip);
        }
    }
    return newpoly;
}
double PolygonArea(Polygon &p) {
    double area=0;
    int n=p.size();
    For(i,n-2) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
} 

//线上不算 
bool OnLeft(Line L,P p) {
    return Cross(L.v,p-L.p)>0;
} 
P GetIntersection(Line a,Line b) {
    V u=a.p-b.p;
    double t = Cross(b.v,u) / Cross(a.v, b.v);
    return a.p + a.v*t;
}
int HalfplaneIntersection(Line *L, int n, P* poly) {
    sort(L,L+n);
    int fi,la;
    P *p = new P[n];
    Line *q = new Line[n];
    q[fi=la=0 ] = L[0];
    For(i,n-1) {
        while (fi < la && !OnLeft(L[i],p[la-1])) la--;
        while (fi < la && !OnLeft(L[i],p[fi])) fi++;
        q[++la] = L[i];
        if (fabs(Cross(q[la].v, q[la-1].v))<eps) {
            la--;
            if (OnLeft(q[la],L[i].p)) q[la] = L[i];
        }
        if (fi<la) p[la-1] = GetIntersection(q[la-1],q[la]);
    }
    while(fi < la && !OnLeft(q[fi],p[la-1])) la--;
    if (la-fi<=1) return 0; 
    p[la] = GetIntersection(q[la],q[fi]);

    int m=0;
    Fork(i,fi,la) poly[m++]=p[i];
    return m;
} 

// hypot(double x,double y); return sqrt(x*x+y*y)

double rotating_calipers(P *p,int n) {
    int q=1;
    double ans=0;
    Rep(i,n) {
        while(fabs(Area2(p[i],p[(i+1)%n],p[(q+1)%n]))> fabs(Area2(p[i],p[(i+1)%n],p[q] )) ) 
            q=(q+1)%n;
        ans = max( ans, (double)max(Length(p[i]- p[q]), Length(p[(i+1)%n] -p[q] ) ) );          
    }
    return ans;
}
// rotating for rect
double rec_rotating_calipers(P *p,int n) {
    int q=1;
    double ans1=1e15,ans2=1e15;
    int l=0,r=0;
    Rep(i,n) {
        while(dcmp(fabs(Area2(p[i],p[(i+1)%n],p[(q+1)%n])) - fabs(Area2(p[i],p[(i+1)%n],p[q] ))) >0  ) 
            q=(q+1)%n;
        while (dcmp(Dot(p[(i+1)%n]-p[i],p[(r+1)%n]-p[r]))>0 )  r=(r+1)%n;
        if (!i) l=q;
        while (dcmp(Dot(p[(i+1)%n]-p[i],p[(l+1)%n]-p[l]))<0 )  l=(l+1)%n;
        double d = Length(p[(i+1)%n]-p[i]);
        double h = fabs(Area2(p[i],p[(i+1)%n],p[q] ))/d;
        double w=(Dot(p[(i+1)%n]-p[i],p[r]-p[i]) - Dot(p[(i+1)%n]-p[i],p[l]-p[i]) ) /d;
        ans1=min(ans1,2*(h+w)),ans2=min(ans2,h*w);
    }
    printf("%.2lf %.2lf\n",ans2,ans1);
}


//去共线化 
void simplify(Polygon& poly) {
    Polygon ans;
    int n=SI(poly);
    Rep(i,n) {
        if (dcmp(Cross(poly[i]-poly[(i+1)%n],poly[(i+1)%n]-poly[(i+2)%n]))!=0)
            ans.pb(poly[(i+1)%n]);
    }
    n=SI(ans);
    cout<<n<<endl;
    Rep(i,n) printf("%.4lf %.4lf\n",ans[i].x,ans[i].y);
}

int getSegCircleIntersection(Line L,C cir,vector<P> & sol) {
    if (dcmp(DistanceToLine(cir.c,L.p,L.p+L.v)-cir.r)==0) {
        P A= GetLineProjection(cir.c,L.p,L.p+L.v);
        if (OnSegment(A,L.p,L.p+L.v) || L.p==A || L.p+L.v==A  ) 
            sol.pb(A);
        return sol.size();
    }
    double t1,t2;
    double a = L.v.x, b = L.p.x - cir.c.x, c = L.v.y, d= L.p.y - cir.c.y;
    double e = a*a+c*c, f = 2*(a*b + c*d), g = b*b+d*d-cir.r*cir.r;
    double delta = f*f - 4*e*g;
    if (dcmp(delta)<0) return 0;
    else if (dcmp(delta)==0) {
        t1 = -f / (2*e); 
        if (dcmp(t1)>=0&&dcmp(t1-1)<=0) {
            sol.pb(L.point(t1));
        }
        return sol.size();
    } 
    t1 = (-f - sqrt(delta)) / (2*e); if (dcmp(t1)>=0&&dcmp(t1-1)<=0) sol.pb(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2*e); if (dcmp(t2)>=0&&dcmp(t2-1)<=0) sol.pb(L.point(t2));
    if(SI(sol)==2 && t1>t2) swap(sol[1],sol[0]);
    return sol.size();
}
int isPointInOrOnCircle(P p,C c) {
    return dcmp(Length(p-c.c)-c.r)<=0;
}

// Triangle(O,A,B) and Circle(O,m)
double CircleTriangleArea(P A,P B,double m) {
    double ans=0;
    C c=C(P(),m); P O=c.c;
    if (A==O||B==O) return 0;
    bool b = isPointInOrOnCircle(A,c);
    bool b2 = isPointInOrOnCircle(B,c);
    double opr;
    if (dcmp(Area2(O,A,B))>=0) opr=1; else opr=-1;
    if (b&&b2) {
        ans+=opr*fabs(Area2(A,B,O))/2; 
    } else if (!b&&!b2){
        Line l=Line(A,B-A);
        vector<P> sol;
        getSegCircleIntersection(l,c,sol);
        if (SI(sol)==2) {
            ans+=opr*fabs(Area2(sol[0],sol[1],O))/2;
            ans+=opr*m*m/2*(Angle(A,sol[0])+Angle(sol[1],B));
        } else {
            ans+=opr*m*m/2*(Angle(A,B));
        }
    } else {
        Line l=Line(A,B-A);
        vector<P> sol;
        getSegCircleIntersection(l,c,sol);
        if (SI(sol)==2) {
            ans+=opr*fabs(Area2(sol[0],sol[1],O))/2;
            ans+=opr*m*m/2*(Angle(A,sol[0])+Angle(sol[1],B));
        } else if(b) { 
            ans+=opr*fabs(Area2(sol[0],A,O))/2;
            ans+=opr*m*m/2*(Angle(sol[0],B));
        } else {
            ans+=opr*fabs(Area2(sol[0],B,O))/2;
            ans+=opr*m*m/2*(Angle(sol[0],A));
        }
    }
    return ans;
}
int n;
#define MAXN (102345)
double area[MAXN];
int Circmp(C a,C b) {return a.r<b.r;}
struct cp {
    double angle;
    int d;
    cp(){}
    cp(double angle,int d):angle(angle),d(d){}
    friend double calc(C c, cp cp1, cp cp2) {
        P A=c.point(cp1.angle),B=c.point(cp2.angle);
        double ans = (cp2.angle - cp1.angle) * c.r* c.r 
            - Cross(c.c-A,c.c-B)+Cross(A,B);
        return ans *0.5;
    }
    friend bool operator<(cp a,cp b){
        if (dcmp(a.angle-b.angle)!=0) return a.angle<b.angle;
        return a.d>b.d;
    }
}tp[MAXN<<1];
void CircleUnion(C c[],int n) {
    MEM(area)
    sort(c,c+n,Circmp);
    int d[MAXN]={};
    Rep(i,n) {
        Fork(j,i,n-1) {
             if (dcmp(Length(c[i].c-c[j].c) + c[i].r - c[j].r )  <= 0)
                d[i]++;
        }
    }
    Rep(i,n) {
        int cnt = 0;
        vector<cp> tp;
        Rep(j,n) if (i^j) {
            vector<P> sol; sol.clear();
            getCircleCircleIntersection(c[i],c[j],sol);
            int sz=SI(sol);
            if (sz < 2) continue;
            cp cp1,cp2;
            cp1.angle = atan2(sol[0].y - c[i].y, sol[0].x - c[i].x);
            cp2.angle = atan2(sol[1].y - c[i].y, sol[1].x - c[i].x);
            cp1.d = 1;    tp.pb(cp1);
            cp2.d = -1;   tp.pb(cp2);
            if (dcmp(cp1.angle - cp2.angle) > 0) cnt++;

        }
        tp.pb(cp(PI, -cnt));
        tp.pb(cp(- PI,cnt));
        sort(ALL(tp));
        int p, s = d[i] + tp[0].d;
        For(j,SI(tp)-1) {
            p = s;  s += tp[j].d;
            area[p] += calc(c[i], tp[j - 1], tp[j]);
        }
    }
    For(i,n) area[i]-=area[i+1];
}
C cir[MAXN];
int main()
{
//  freopen("A.in","r",stdin);
//  freopen(".out","w",stdout);
    while(cin>>n) {
        Rep(i,n) {
            cir[i]=C(read_point());
            scanf("%lf",&cir[i].r);
        }
        CircleUnion(cir,n);
        For(i,n) printf("[%d] = %.3lf\n",i,area[i]);
    }
    return 0;
}
