#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef double ld;

const int N = 1010;
const double eps = 1e-13;
int n, cnt = 0, st, ed;
ld xl[N], xr[N];
bool del[N];

struct Point{
    ld x, y, r;
}s[N], t[N];/**圆*/

struct line{
    ld x, y;
    bool operator < (const line &rhs) const{
        return x < rhs.x;
    }/**按线段的下端升序排序*/
}p[N];

int cmp1(Point a, Point b){return a.r < b.r;}/**按半径升序排序*/
int cmp2(Point a, Point b){return a.x - a.r < b.x - b.r;}
/**按圆最左端升序排序*/
double dis(Point a, Point b){return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}

ld cal(ld h, ld fa, ld fmid, ld fb){return h * (fa + fmid * 4 + fb) / 6;}/**积分公式*/

ld getf(ld x){
    int sz = 0;
    for(int i = st; i <= ed; ++i){/**穿过x = x直线的圆存入p*/
        if(x <= xl[i] || x >= xr[i]) continue;
        ld tmp = sqrt(t[i].r - (x - t[i].x) * (x - t[i].x));
        p[++sz].x = t[i].y - tmp;/**和当前圆的两交点y坐标*/
        p[sz].y = t[i].y + tmp;
    }
    sort(p + 1, p + sz + 1);
    int j;
    ld res = 0;
    for(int i = 1; i <= sz; ++i){/**纵向找*/
        ld x = p[i].x, y = p[i].y;
        for(j = i + 1; j <= sz; ++j){
            if(p[j].x >= y) break;
            if(p[j].y > y) y = p[j].y;
        }
        res += y - p[i].x; i = j - 1;
    }
    return res;
}

ld simpson(ld l, ld mid, ld r, ld fl, ld fmid, ld fr, ld x){
    ld lmid = (l + mid) / 2, flmid = getf(lmid);
    ld rmid = (mid + r) / 2, frmid = getf(rmid);
    ld la = cal(mid - l, fl, flmid, fmid);
    ld ra = cal(r - mid, fmid, frmid, fr);
    if(fabs(la + ra - x) < eps) return x;
    return simpson(l, lmid, mid, fl, flmid, fmid, la) + simpson(mid, rmid, r, fmid, frmid, fr, ra);
}

int main(){
    memset(del, 0, sizeof del);

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%lf%lf%lf", &s[i].x, &s[i].y, &s[i].r);
    sort(s + 1, s + n + 1, cmp1);
/**r升序*/
    for(int i = 1; i <= n; ++i){
        if(del[i]) continue;
        for(int j = i + 1; j <= n; ++j){
            if(del[j]) continue;
            if(dis(s[i], s[j]) <= s[j].r - s[i].r || fabs(s[i].r) < eps) del[i] = 1;/**去除退化成点或者被包含的圆*/
        }
    }
    for(int i = 1; i <= n; ++i) if(!del[i]) t[++cnt] = s[i];
    sort(t + 1, t + cnt + 1, cmp2);/**剩下的排序*/

    for(int i = 1; i <= cnt; ++i){
        xl[i] = t[i].x - t[i].r;/**存左右端横坐标*/
        xr[i] = t[i].x + t[i].r;
        t[i].r *= t[i].r;
    }

    int j; ld l, r, mid, fl, fr, fmid, ans = 0;
    for(int i = 1; i <= cnt; ++i){/**先找块*/
        l = xl[i], r = xr[i];
        for(j = i + 1; j <= cnt; ++j){
            if(xl[j] >= r) break;/**和前面的块没有交点*/
            if(xr[j] > r) r = xr[j];
        }
        st = i, ed = j - 1;
        i = j - 1;/**下一块前一个位置*/
        mid = (l + r) / 2;
        /**cout << st << " " << ed << " " << mid << endl;*/
        fl = getf(l);/**求f*/
        fmid = getf(mid);
        fr = getf(r);
        ans += simpson(l, mid, r, fl, fmid, fr, cal(r - l, fl, fmid, fr));/**积分求该块面积*/
    }
    printf("%.3lf\n", ans);
    return 0;
}
