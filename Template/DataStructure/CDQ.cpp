const int N = 200005;
int p1, p2, pos, n, k, nn, ans[N];
struct node{
	int x, y, z, num, ans;
	bool operator == (const node & b) const{
		return x == b.x && y == b.y && z == b.z;
	}
} a[N], tmp[N];
bool cmp(node a, node b){
	if (a.x != b.x) return a.x < b.x;
	if (a.y != b.y) return a.y < b.y;
	return a.z < b.z;
}
bool cmp2(node a, node b){
	//if (a.y != b.y) return a.y < b.y;
	//return a.z < b.z;
	return a.y < b.y;
}
void CDQ(int l, int r){
	if (l == r) {
		a[l].ans = a[l].num - 1;
		return;
	}
	int mid = l + r >> 1;
	CDQ(l, mid); CDQ(mid+1, r);
	pos = l;
	rep(i, mid+1, r+1) {
		while (pos <= mid && a[pos].y <= a[i].y) {
			fen.add(fen.a1, a[pos].z, a[pos].num);
			pos++;
		}
		a[i].ans += fen.sum(fen.a1, a[i].z);
	}
	rep(i, l, pos) fen.add(fen.a1, a[i].z, -a[i].num);
	p1 = l; p2 = mid+1;
	rep(i, l, r+1){
		if (p1 > mid) {tmp[i] = a[p2]; p2++;}
		else if (p2 > r) {tmp[i] = a[p1]; p1++;}
		else if (a[p1].y <= a[p2].y) {tmp[i] = a[p1]; p1++;}
		else  {tmp[i] = a[p2]; p2++;}
 	}
 	rep(i, l, r+1) a[i] = tmp[i];
}

int main(){
	cin >> n >> k;
	rep(i, 1, n+1) cin >> a[i].x >> a[i].y >> a[i].z;
	sort(a+1, a+n+1, cmp);
	nn = 0;
	rep(i, 1, n+1) {
		if (i > 1 && a[i] == a[i-1]) { a[nn].num++;
		} else {
			a[++nn] = a[i];
			a[nn].num = 1;
		}
	}
	fen.ini(N);
	CDQ(1, nn);
	rep(i, 1, nn+1) ans[a[i].ans] += a[i].num;
	rep(i, 0, n) cout << ans[i] << endl;
	return 0;
}
