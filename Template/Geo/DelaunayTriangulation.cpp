typedef __int128 T;
const int N = 1e4 + 10 , NODE = N * 20;
const T eps = 0 , inf = 1e8;// be careful with inf
int sgn(T x){return (x>eps)-(x<-eps);}
struct P{
  T x,y;int id;P(){} P(T x,T y,int id=0):x(x),y(y),id(id){}
  P operator - (const P&b) const {return P(x-b.x,y-b.y);}
  T operator * (const P&b) const {return x*b.x+y*b.y;}
  T operator / (const P&b) const {return x*b.y-y*b.x;}
};
T norm(P a){return a*a;}
T cross(P a,P b,P p){return (b-a)/(p-a);}
// be careful with integer limitation
bool inCir(P a,P b,P c,P p){
  T A = (b - p) / (c - p) * (norm(a) - norm(p));
  T B = (c - p) / (a - p) * (norm(b) - norm(p));
  T C = (a - p) / (b - p) * (norm(c) - norm(p));
  return sgn(A + B + C) > 0;
}
struct Tri;
struct Edge{
  Tri* tri;int side;
  Edge(Tri* tri=NULL,int side=0):tri(tri),side(side){}
};
struct Tri{
  P p[3];Edge edge[3];Tri*son[3];Tri(){}
  Tri(P p0,P p1,P p2){p[0]=p0,p[1]=p1,p[2]=p2;rep(i,0,3) son[i]=NULL;}
  bool has_son() const {return son[0];}
  bool contains(P q) const {
    rep(i,0,3) if(sgn(cross(p[i],p[(i+1)%3],q))<0) return false;
    return true;
  }
}tri_pool[NODE],*pt;
void set_edge(Edge a,Edge b){
  if(a.tri) a.tri->edge[a.side]=b;
  if(b.tri) b.tri->edge[b.side]=a;
}
Tri* root;
// use bfs to handle in-line case
Tri* find(P p){
  Tri*c=root;
  while(c->has_son()) rep(i,0,3)
    if(c->son[i]->contains(p))
    {c=c->son[i];break;}
  return c;
}
void flip(Tri*x,int px){
  Tri* y=x->edge[px].tri;int py=x->edge[px].side;
  if(!y||!inCir(x->p[0],x->p[1],x->p[2],y->p[py])) return;
  Tri*s[2];
  s[0]=new(pt++) Tri(x->p[(px+1)%3],y->p[py],x->p[px]);
  s[1]=new(pt++) Tri(y->p[(py+1)%3],x->p[px],y->p[py]);
  set_edge(Edge(s[0],0),Edge(s[1],0));
  set_edge(Edge(s[0],1),x->edge[(px+2)%3]),set_edge(Edge(s[0],2),y->edge[(py+1)%3]);
  set_edge(Edge(s[1],1),y->edge[(py+2)%3]),set_edge(Edge(s[1],2),x->edge[(px+1)%3]);
  rep(i,0,2) x->son[i]=y->son[i]=s[i];
  x->son[2]=y->son[2]=0;
  rep(i,0,2) flip(s[i],1),flip(s[i],2);
}
void add(P p){
  Tri*c=find(p),*s[3];
  rep(i,0,3) c->son[i]=s[i]=new(pt++) Tri(c->p[i],c->p[(i+1)%3],p);
  rep(i,0,3) set_edge(Edge(s[i],0),Edge(s[(i+1)%3],1));
  rep(i,0,3) set_edge(Edge(s[i],2),c->edge[(i+2)%3]);
  rep(i,0,3) flip(s[i],2);
}
void init(P*p,int n){
  pt=tri_pool;
  root=new(pt++) Tri(P(-inf,-inf),P(inf,-inf),P(0,inf));
  random_shuffle(p,p+n);
  rep(i,0,n) add(p[i]);
}
