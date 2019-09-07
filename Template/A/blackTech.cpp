clock_t st = clock();
CLOCKS_PER_SEC;
mt19937 gen(998244353);
typedef uniform_int_distribution<ll> RR;
ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
typedef uniform_real_distribution<db> RR;
db rnd(db l, db r) { RR dis(l, r); return dis(gen); }
