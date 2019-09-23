/*
 * 平面图欧拉定理：V + F - E = 2
 */
 bool cmp(const pii &a, const pii &b) { // 级角排序
	int o = a > pii(0, 0), t = b > pii(0, 0);
	if(o != t) return o < t;
	return det(a, b) > 0;
}
P isLL(L l, db a, db b, db c) {
	db u = a * l.a.x + b * l.a.y + c;
	db v = -(a * l.b.x + b * l.b.y + c);
	return (l.a * v + l.b * u) / (u + v);
}
P isLL(db a0, db b0, db c0, db a1, db b1, db c1) {
	db d = a0 * b1 - a1 * b0;
	return P(b0 * c1 - b1 * c0, a1 * c0 - a0 * c1) / d;
}
bool isSSr(const L &a, const L &b){ // 线段规范相交
	db c1 = det(a.t - a.s, b.s - a.s), c2 = det(a.t - a.s, b.t - a.s),
		 c3 = det(b.t - b.s, a.s - b.s), c4 = det(b.t - b.s, a.t - b.s);
	return sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0;
}
bool isSS(L a,L b){ // 线段不规范相交
	db c1 = det(a.t - a.s, b.s - a.s), c2 = det(a.t - a.s, b.t - a.s),
		 c3 = det(b.t - b.s, a.s - b.s), c4 = det(b.t - b.s, a.t - b.s);
	return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0 &&
		sign(max(a.s.x, a.t.x) - min(b.s.x, b.t.x)) >= 0 &&
		sign(max(b.s.x, b.t.x) - min(a.s.x, a.t.x)) >= 0 &&
		sign(max(a.s.y, a.t.y) - min(b.s.y, b.t.y)) >= 0 &&
		sign(max(b.s.y, b.t.y) - min(a.s.y, a.t.y)) >= 0;
}
db disSS(L a, L b){ // 线段到线段距离
	if(isSS(a, b)) return 0;
	return min(min(disToSeg(b, a.s), disToSeg(b, a.t)), min(disToSeg(a, b.s), disToSeg(a, b.t)));
}
// 判断直线线段是否相交（端点也算）
bool isLS(P a1, P a2, P b1, P b2) {
    db c1 = det(a2 - a1, b1 - a1), c2 = det(a2 - a1, b2 - a1);
    return sign(c1) * sign(c2) <= 0;
}
P outC(P A, P B, P C) { // 外心
	P b = B - A, c = C - A;
	db dB = b.len2(), dC = c.len2(), d = 2 * det(b, c);
	return A - P(b.y * dC - c.y * dB, c.x * dB - b.x * dC) / d;
}
bool isconvex(vector<P> A) { // 判断是否是凸包 逆时针
	bool ok = 1;
	int n = sz(A);
	rep(i, 0, 2) A.pb(A[i]);
	rep(i, 0, n) ok &= det(A[i + 1] - A[i], A[i + 2] - A[i]) >= 0;
	return ok;
}
db diameter(vector<P> A) { // 求凸包最远点对
	int n = sz(A);
	if(n <= 1) return 0;
	int l = 0, r = 0;
	rep(i, 1, n) (A[i] < A[l]) && (l = i), (A[r] < A[i]) && (r = i);
	db res = (A[l]-A[r]).len();
	int i = l, j = r;
	do (++(det(A[(i + 1) % n]- A[i], A[(j + 1) % n] - A[j]) >= 0 ? j : i)) %= n,
		res = max(res, (A[i] - A[j]).len());
	while(i != l || j != r);
	return res;
}
// sz(A) <= 100,000
namespace NearestPoints { // 点集中最近点对
	db solve(int l, int r, vector<P> &p) {
		if(l == r) return 1e100;
		int m = l + r >> 1;
		db Xm = p[m].x, lim = min(solve(l, m, p), solve(m + 1, r, p));
		inplace_merge(p.begin() + l, p.begin() + m + 1, p.begin() + r + 1, [&](P a, P b){return a.y < b.y;});
		vector<P> V;
		rep(i, l, r + 1) if(fabs(p[i].x - Xm) <= lim) V.pb(p[i]);
		rep(i, 0, sz(V)) rep(j, i + 1, sz(V)) {
			if(fabs(V[j].y - V[i].y) >= lim) break;
			T dis = (V[i] - V[j]).len();
			lim = min(lim, dis);
		}
		return lim;
	}
	db solve(vector<P> A) {
		sort(all(A), [&](P a, P b){return a.x < b.x;});
		return solve(0, sz(A) - 1, A);
	}
}
// 注意相等关系
// 4:相离 3:外切 2:相交 1:内切 0:内含
int relCC(C A, C B) { // 两圆关系
	db dis = (A.o - B.o).len();
	if(sign(dis - (A.r + B.r)) == 1) return 4;
	if(sign(dis - (A.r + B.r)) == 0) return 3;
	if(sign(dis - fabs(A.r - B.r)) == 1) return 2;
	if(sign(dis - fabs(A.r - B.r)) == 0) return 1;
	return 0;
}
vector<P> tanCC(const C &c1, const C &c2) { // 求圆与圆的切点
	vector<P> res;
	db dis = (c1.o - c2.o).len();
	if(sign(dis - (c1.r + c2.r)) == 0) {
		res.pb(c1.o + (c2.o - c1.o) * c1.r / (c1.r + c2.r));
	}
	if(sign(dis - fabs(c1.r - c2.r) == 0)) {
		res.pb(c1.o + (c2.o - c1.o) * c1.r / (c1.r - c2.r));
	}
	return res;
}
db rad(P p1, P p2) { return atan2l(det(p1, p2), dot(p1, p2)); } // p1 与 p2 的夹角，有方向
db areaCT(db r,P s,P t) { // 求圆与三角形交面积，需要除2
	P p1, p2;
	bool f = isCL(C(P(0, 0), r), L(s, t), p1, p2);
	if(!f) return r * r * rad(s, t);
	bool b1 = sign(s.len2() - r * r) == 1 , b2 = sign(t.len2() - r * r) == 1;
	if(b1 && b2) {
		if(sign(dot(s - p1, t - p1)) <= 0 && sign(dot(s - p2, t - p2) <= 0))
			return r * r * (rad(s, p1) + rad(p2, t)) + det(p1, p2);
		else return r * r * rad(s, t);
	} else if(b1) return r * r * rad(s, p1) + det(p1, t);
	else if(b2) return r * r * rad(p2, t) + det(s, p2);
	return det(s, t);
}
db areaCPoly(C c, vector<P> p) { // 求圆与多边形交面积
	int n = sz(p);
	db ans = 0;
	rep(i, 0, n) {
		P u = p[i], v = p[(i + 1) % n];
		ans += areaCT(c.r, u - c.o, v - c.o);
	}
	return fabs(ans) / 2;
}
C Mincir(P *p,int n){ // 最小圆覆盖
	random_shuffle(p , p + n);
	P o = p[0];db r = 0;
	rep(i,1,n) {
		if(sgn(abs(o-p[i])-r) <= 0) continue;
		o = p[i] , r = 0;
		rep(j,0,i) {
			if(sgn(abs(o-p[j])-r) <= 0) continue;
			o = (p[i] + p[j]) / 2 , r = abs(o-p[j]);
			rep(k,0,j) {
				if(sgn(abs(o-p[k])-r) <= 0) continue;
				o = outC(p[i],p[j],p[k]) , r = abs(o-p[k]);
			}}}
	return C(o,r);
}
namespace CircleIntersection{ // ?
	struct E{
		P p;T ang;int delta;
		E(){} E(P p,T ang,int delta):p(p),ang(ang),delta(delta){}
		bool operator < (const E&b) const {return ang<b.ang;}
	};
	bool overlap(C a,C b) {return sgn(a.r-b.r-abs(a.o-b.o))>=0;}
	void solve(C *c,int n,T *ans) {
		memset(ans , 0 , sizeof(T) * (n + 1));
		rep(i,0,n) {
			int cnt=1;
			vector<E> evt;
			rep(j,0,i) if(c[i]==c[j]) cnt++;
			rep(j,0,n) if(j!=i&&!(c[i]==c[j])&&overlap(c[j],c[i])) cnt++;
			rep(j,0,n) if(j!=i){
				vector<P> pts=insCC(c[i],c[j]);
				if(sz(pts)) {
					T a[2];
					rep(j,0,2) a[j]=(pts[j]-c[i].o).arg();
					evt.pb(E(pts[0],a[0],1));
					evt.pb(E(pts[1],a[1],-1));
					cnt += a[0] > a[1];
				}
			}
			if(!sz(evt)) ans[cnt] += pi*c[i].r*c[i].r;
			else{
				sort(all(evt));
				evt.pb(evt.front());
				rep(j,0,sz(evt)-1) {
					cnt+=evt[j].delta;
					ans[cnt] += evt[j].p / evt[j+1].p / 2;
					db ang = evt[j + 1].ang - evt[j].ang;
					if(ang < 0) ang += pi * 2;
					ans[cnt] += ang * c[i].r * c[i].r / 2 - sin(ang) * c[i].r * c[i].r / 2;
				}}}}}
namespace ConvecIntersection{ // ?
	const int N = 1005;
	struct Rec {
		P d[10];int dn;// d[dn] = d[0]
		P operator [] (const int&n) {return d[n];}
	}r[N];
	typedef pair<db,int> pdi;
	int n;pdi res[1000005];
	db getLoc(P a,P b,P p){
		if(sgn(b.x - a.x)) return (p.x - a.x) / (b.x - a.x);
		return (p.y - a.y) / (b.y - a.y);
	}
	db work() {
		db rt=0;
		rep(i,0,n) rep(j,0,r[i].dn){
			int sz=0;
			res[sz++] = pdi(0,0);res[sz++] = pdi(1,0);
			rep(t,0,n) {
				if(t == i) continue;
				rep(g,0,r[t].dn) {
					int du = sgn((r[i][j+1] - r[i][j]) / (r[t][g] - r[i][j]));
					int dv = sgn((r[i][j+1] - r[i][j]) / (r[t][g+1] - r[i][j]));
					if(!du && !dv) {
						if(sgn((r[i][j+1] - r[i][j]) * (r[t][g+1] - r[t][g])) < 0 || i < t){
							res[sz++] = pdi(getLoc(r[i][j] , r[i][j+1] , r[t][g]) , 1);
							res[sz++] = pdi(getLoc(r[i][j] , r[i][j+1] , r[t][g+1]) , -1);
						}} else {
							db s1 = (r[i][j] - r[t][g]) / (r[t][g+1] - r[t][g]);
							db s2 = (r[t][g+1] - r[t][g]) / (r[i][j+1] - r[t][g]);
							if(du >= 0 && dv < 0) res[sz++] = pdi(s1 / (s1 + s2) , 1);
							else if(du < 0 && dv >= 0) res[sz++] = pdi(s1 / (s1 + s2) , -1);
						}}}
			sort(res , res + sz);
			int cnt = 0; --sz;
			rep(t,0,sz) {
				cnt += res[t].se;
				if(cnt == 0 && sgn(res[t].fi - res[t+1].fi)) {
					db a = res[t].fi;
					if(a < 0) a = 0; if(a > 1) break;
					db b = res[t+1].fi;
					if(b < 0) continue; if(b > 1) b = 1;
					rt += ((r[i][j+1] - r[i][j]) * a + r[i][j]) / ((r[i][j+1]-r[i][j]) * b + r[i][j]);
				}}}
		return rt / 2;}}
