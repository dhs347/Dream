
#define rep(i, a, b) for(int i=(a); i<(b); i++)
typedef double db;
const double eps=1e-8;
const double PI=acos(-1);

//负数-1 零0 正数1
int sgn(db x) {
    return (x > eps) - (x < -eps);
}
struct P {
    db x,y;
    P() {}
    P(db _x, db _y) {x = _x, y = _y;}
    P operator - (const P&b) const{
        return P(x - b.x, y - b.y);
    }
    P operator + (const P&b) const {
        return P(x + b.x, y + b.y);
    }
    P operator * (const db&c) const {
        return P(x * c, y * c);
    }
    P operator / (const db&c) const {
        return P(x / c, y / c);
    }
    bool operator < (const P&b) const {
        int f = sgn(x - b.x);
        return f ? (f < 0) : (sgn(y - b.y) < 0);
    }
    bool operator == (const P&b) const {
        return !sgn(x - b.x) && !sgn(y - b.y);
    }

    void print(char c) {
        printf("%.6f %.6f%c",x,y,c);
    }
};

P read() {
    db x,y;
    scanf("%lf%lf",&x,&y);
    return P(x,y);
}
db cross(P a, P b) {
    return a.x * b.y - a.y * b.x;
}
db dot(P a, P b) {
    return a.x * b.x + a.y * b.y;
}

db abs(P a) {
    return sqrt(a.x * a.x + a.y * a.y);
}
db norm(P a) {
    return a.x * a.x + a.y * a.y;
}
//两点距离
db dis(P a, P b) {
    return sqrt(norm(a - b));
}
//向量ab与x轴的夹角 弧度 (-PI,PI]
db ang(P a, P b) {
    return atan2(b.y - a.y, b.x - a.x);
}
//向量oa与ob的夹角 弧度 [0,PI]
db ang(P a, P o, P b) {
    return acos(dot(a - o, b - o) / abs(a - o) / abs(b - o));
}
//向量逆时针旋转rad（弧度）
P rot(P a, db rad) {
    return P(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}
//逆时针旋转90度
P rot90(P p) {
    return P(-p.y, p.x);
}
//oa向量逆时针旋转rad（弧度）后a的位置
P rot(P a, P o, db rad) {
    return rot(a - o, rad) + o;
}

//直线pv和qw的交点
P insLL(P p, P v, P q, P w) {
    P u = p - q;
    v = v - p;
    w = w - q;
    db t = cross(w, u) / cross(v, w);
    return p + v * t;
}

//判断线段是否规范相交（交点不在任一个端点上）
bool isSS0(P a1, P a2, P b1, P b2) {
    db c1 = cross(a2 - a1, b1 - a1);
    db c2 = cross(a2 - a1, b2 - a1);
    db c3 = cross(b2 - b1, a1 - b1);
    db c4 = cross(b2 - b1, a2 - b1);
    return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}

//判断线段是否不规范相交
bool isSS1(P a1, P a2, P b1, P b2) {
    db c1 = cross(a2 - a1, b1 - a1);
    db c2 = cross(a2 - a1, b2 - a1);
    db c3 = cross(b2 - b1, a1 - b1);
    db c4 = cross(b2 - b1, a2 - b1);
    return sgn(max(a1.x, a2.x) - min(b1.x, b2.x)) >=0 &&
    sgn(max(b1.x, b2.x) - min(a1.x, a2.x)) >=0 &&
    sgn(max(a1.y, a2.y) - min(b1.y, b2.y)) >=0 &&
    sgn(max(b1.y, b2.y) - min(a1.y, a2.y)) >=0 &&
    sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0;
}
//判断点是否在线段上（不包括端点）
bool onS0(P p, P a, P b) {
    return sgn(cross(p - a, b - a)) == 0 && sgn(dot(p - a, p - b)) < 0;
}
//判断点是否在线段上（包括端点）
bool onS1(P p, P a, P b) {
    return sgn(cross(p - a, b - a)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}
//判断两直线是否相交
bool isLL(P a1, P a2, P b1, P b2) {
	return sgn(cross(a2 - a1, b2 - b1)) != 0;
}
//点p到直线距离
db distoL(P p, P a, P b) {
    return fabs(cross(b - a, p - a)) / abs(b - a);
}
//点p到线段距离
db distoS(P p, P a, P b) {
    if(sgn(dot(b - a, p - a)) < 0) return abs(p - a);
    if(sgn(dot(a - b, p - b)) < 0) return abs(p - b);
    return distoL(p, a, b);
}

//直线两点式转一般式
//直线的一般式：Ax+By+C=0
void getLABC(P a, P b, db &A, db &B, db &C) {
    A = a.y - b.y;
	B = b.x - a.x;
	C = a.x * b.y - a.y * b.x;
}
//多边形面积
db areaP(P *p, int n) {
    db ans = 0; p[n] = p[0];
    rep(i,0,n) ans += cross(p[i], p[i+1]);
    return fabs(ans/2.0);
}
//判断点和多边形的关系 边上-1 外0 内1
int PinPloy(P o, P *p, int n) {
    int res = 0;
    rep(i,0,n) {
        P a = p[i], b = p[(i+1)%n];
        if(onS1(o, a, b)) return -1;
        int k = sgn(cross(b - a, o - a));
        int d1 = sgn(a.y - o.y);
        int d2 = sgn(b.y - o.y);
        if(k > 0 && d1 <= 0 && d2 > 0) ++res;
        if(k < 0 && d2 <= 0 && d1 > 0) --res;
    }
    return res!=0;
}

//求凸包：把给定点包围在内部的，面积最小的凸多边形
//复杂度：O(n) 加上排序：O(nlogn)
//输入的点要先去重
//如果不希望在凸包的边上有输入点，把两个 <= 改成 <
int convexHull(P *p, int n, P *ch) {
    sort(p,p+n);
    int m=0;
    rep(i,0,n) {
        while(m>1&&sgn(cross(ch[m-1] - ch[m-2], p[i] - ch[m-2])) <= 0) --m;
        ch[m++] = p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;--i) {
        while(m>k&&sgn(cross(ch[m-1] - ch[m-2], p[i] - ch[m-2])) <= 0) --m;
        ch[m++] = p[i];
    }
    return m - (n > 1);
}
db RC(P *ch, int n) {
    int q=1; db ans=0; ch[n]=ch[0];
    rep(p,0,n) {
        while(cross(ch[q+1] - ch[p+1], ch[p] - ch[p+1]) > cross(ch[q] - ch[p+1], ch[p] - ch[p+1])) q=(q+1)%n;
        ans = max(ans, max(abs(ch[p] - ch[q]), abs(ch[p+1] - ch[q+1])));
    }
    return ans;
}


//---------------
//判断直线线段是否相交（端点也算）
bool isLS(P a1, P a2, P b1, P b2) {
    db c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
    return sgn(c1) * sgn(c2) <= 0;
}

//向量p在向量v方向上的投影（点）
P proj(P p, P v) {
    return v * dot(p, v) / norm(v);
}
//向量ap在向量ab方向上的投影（点）
P proj(P p, P a, P b) {
    return proj(p - a, b - a) + a;
}
//p点在关于ab的对称点
P reflect(P p, P a, P b) {
    P o = proj(p, a, b);
    return o * 2 - p;
}


