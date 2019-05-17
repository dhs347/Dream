#include <iostream>
#include <stdio.h>
using namespace std;
#define re(i, n) for (int i=0; i<n; i++)
const int MAXN = 100001, INF = ~0U >> 2;
struct node {
int v, c[2], p, sz, mul;
bool d;
} T[MAXN];
int n = 0, root, res, tot = 0;

void upd(int x){
	T[x].sz = T[T[x].c[0]].sz + T[T[x].c[1]].sz + T[x].mul;
}

void sc(int _p, int _c, bool _d){
	T[_p].c[_d] = _c; T[_c].p = _p; T[_c].d = _d;
}

void rot(int x){
	int y = T[x].p, d = T[x].d;
	if (y == root) {root = x; T[root].p = 0;} else sc(T[y].p, x, T[y].d);
	sc(y, T[x].c[!d], d); sc(x, y, !d); upd(y); upd(x);
}

void splay(int x, int r){
	int i = x, p, p0;
	while ((p0 = T[i].p) != r) {
		p = T[p0].p;
		if (p == r) rot(i); else 
		if (T[i].d == T[p0].d) {rot(p0); rot(i);} 
		else {rot(i); rot(i);}
	}
}

void ins(int _v){
	if (!root) {
		T[++n].v = _v; 
		T[n].c[0] = T[n].c[1] = T[n].p = 0; 
		T[n].sz = T[n].mul = 1; 
		root = n; 
		return;
	}
	int i = root, j;
	while (1) {
		T[i].sz++;
		if (T[i].v == _v) {
			T[i].mul++; 
			splay(i, 0); 
			return;
		}
		j = T[i].c[_v > T[i].v];
		if (!j) break; else i = j;
	}
	T[++n].v = _v; 
	T[n].c[0] = T[n].c[1] = 0; 
	T[n].sz = T[n].mul = 1; 
	sc(i, n, _v > T[i].v); 
	splay(n, 0);
}

void del(int lmt){
	if (!root) return;
	int i = root, _min = INF, b = 0, v0;
	while (i) {
		v0 = T[i].v;
		if (v0 == lmt) {b = i; break;}
		if (v0 < lmt) i = T[i].c[1]; else {
			if (v0 < _min) {_min = v0; b = i;} 
			i = T[i].c[0];
		}
	}
	if (!b) {tot += T[root].sz; root = 0;} else {
		splay(b, 0); tot += T[T[root].c[0]].sz;
		T[T[root].c[0]].p = 0; T[root].c[0] = 0; upd(root);
	}
}

int Find_Kth(int K){
	int i = root, s0, m0;
	while (1) {
		s0 = T[T[i].c[0]].sz; m0 = T[i].mul;
		if (K <= s0) i = T[i].c[0]; else 
		if (K <= s0 + m0) return T[i].v; else {
			K -= s0 + m0; i = T[i].c[1];
		}
	}
}

int main(){
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
	
	int m, minv, delt = 0, x;
	char ch;
	scanf("%d%d%*c", &m, &minv);
	re(i, m) {
		scanf("%c%d%*c", &ch, &x);
		switch(ch) {
			case 'I': {if (x >= minv) ins(x - delt); break;}
			case 'A': {delt += x; break;}
			case 'S': {delt -= x; del(minv - delt); break;}
			case 'F': if (T[root].sz - x + 1 <= 0) printf("%d\n", -1); else 
					printf("%d\n", Find_Kth(T[root].sz - x + 1) + delt);
		}
	}
	printf("%d\n", tot);
	
	return 0;
}
