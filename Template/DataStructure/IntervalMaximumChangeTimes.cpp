inline int qry(int L, int R, ll &v, int o, bool spe, int l, int r, int rt) {
  if(L > R) return 0;
  if(!spe) {
    if(ma[rt] < v) return 0;
    if(L <= l && r <= R) {
      if(l == r) return v = ma[rt], 1;
      int mid = l + r >> 1;
      down(l, r, mid, rt);
      if(ma[ls | o] < v) return o ? qry(L, R, v, o, 0, l, mid, ls) : qry(L, R, v, o, 0, mid + 1, r, rs);
      int ans = cnt[rt][o] - cnt[ls | o][o] + (o == 0 ? qry(L, R, v, o, 0, l, mid, ls) : qry(L, R, v, o, 0, mid + 1, r, rs));
      return v = ma[rt], ans;
    }
  }
  int mid = l + r >> 1, ans = 0;
  down(l, r, mid, rt);
  if(o == 0 && L <= mid) ans += qry(L, R, v, o, 0, l, mid, ls);
  if(R > mid) ans += qry(L, R, v, o, 0, mid + 1, r, rs);
  if(o == 1 && L <= mid) ans += qry(L, R, v, o, 0, l, mid, ls);
  return ans;
}
void up(int l, int r, int rt) {
  ma[rt] = max(ma[ls], ma[rs]);
  rep(o, 0, 2) { ll v = 0; cnt[rt][o] = qry(l, r, v, o, 1, l, r, rt); }
}
