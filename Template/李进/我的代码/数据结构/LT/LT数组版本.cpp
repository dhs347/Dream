#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
const int oo=(1<<30);
using namespace std;
struct LTNode{
    int l,r,d,key,s;
	LTNode(int x=0) : l(0),r(0),key(x),d(0),s(x!=oo) {}
};

vector <LTNode> _T(1,LTNode(oo));

void print(int t){
	if (!t) return;
	print(_T[t].l);
	printf("%d ",_T[t].key);
	print(_T[t].r);
}

int merge(int x,int y){
    if (!x || !y) return x+y;
    int k=_T[x].s+_T[y].s;
    if(_T[x].key > _T[y].key) swap(x,y);
    _T[x].r = merge(_T[x].r,y);
    if(_T[_T[x].l].d < _T[_T[x].r].d) swap(_T[x].l,_T[x].r);
    _T[x].d = (_T[_T[x].r].d + 1)*(_T[x].r>0);
    _T[x].s=k;
    return x;
}

void insert(int &t,int x){
	_T.push_back(LTNode(x));
	t = merge(t,(int)_T.size()-1);
}

int extract(int &t){
	int x=t; t=merge(_T[t].l,_T[t].r);
	return x;
}

int build(int a[],int l,int r){
	queue <int> Q;
	int x,y;
	for (int i=l; i<=r; i++) {
		_T.push_back(LTNode(a[i]));
		Q.push((int)_T.size()-1);
	}
	while (!Q.empty()){
		if (Q.size()==1) return Q.front();
		x=Q.front(),Q.pop();
		y=Q.front(),Q.pop();
		Q.push(merge(x,y));
	}
}
