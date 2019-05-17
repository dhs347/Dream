const int N = 130;
typedef bool BB[N];
struct Maxclique {
    const BB *e; int pk, lv; db Tlimit;
    struct ve {int i, d; ve(int i): i(i),d(0) {}}; //ve : Vertex
    struct sc {int a, b; sc(     ): a(0),b(0) {}}; //sc : StepCount
    typedef vector<ve> ves; ves V;                 //ves: Vertices
    typedef vector<int> cc; cc  Q, QMAX;           //cc : ColorClass
    vector<cc> C;
    vector<sc> S;
    Maxclique(BB *conn, int sz, const db tt = 0.025): pk(0), lv(1), Tlimit(tt) {
        rep(i, 0, sz) V.pb(ve(i)); e = conn;
        C.resize(sz + 1);
        S.resize(sz + 1);
    }
    static bool desc_deg(const ve &a, const ve &b) { return a.d > b.d; }
    void ini_col(ves &v) { per(i, 0, sz(v)) v[i].d = min(i, v[0].d) + 1; }
    void set_deg(ves &v) { rep(i, 0, sz(v)){v[i].d = 0; rep(j, 0, sz(v)) v[i].d += e[v[i].i][v[j].i]; } }
    void deg_sort(ves &R) { set_deg(R); sort(all(R), desc_deg); }
    bool cut1(int pi , cc  &va) { rep(i, 0, sz(va)) if (e[pi][va[i]]) return true; return false; }
    void cut2(ves &va, ves &vb) { rep(i, 0, sz(va) - 1) if (e[va.back().i][va[i].i]) vb.pb(va[i].i); }
    void co_sort(ves &R) {
        int j = 0, maxno = 1, min_k = max(sz(QMAX) - sz(Q) + 1, 1);
        rep(i, 1, 3) C[i].clear();
        rep(i, 0, sz(R)) {
            int pi = R[i].i, k = 1;
            while (cut1(pi, C[k])) k++;
            if (k > maxno) C[(maxno = k) + 1].clear(); C[k].pb(pi);
            if (k < min_k) R[j++].i = pi;
        }
        if (j > 0) R[j - 1].d = 0;
		rep(k, min_k, maxno + 1)
            rep(i, 0, sz(C[k]))
                R[j].i = C[k][i], R[j++].d = k;
    }
    void exp_dyn(ves &R) {	// expand_dyn
        S[lv].a += S[lv - 1].a - S[lv].b;
        S[lv].b  = S[lv - 1].a;
        for (; sz(R); Q.pop_back(), R.pop_back()) {
            if (sz(Q) + R.back().d <= sz(QMAX)) return;
            Q.pb(R.back().i);
            ves Rp; cut2(R, Rp);
            if (sz(Rp)) {
                if ((db) S[lv].a / ++pk < Tlimit) deg_sort(Rp);
                co_sort(Rp); S[lv++].a++;
                exp_dyn(Rp); --lv;
            } else if (sz(Q) > sz(QMAX)) QMAX = Q;
        }
    }
    void mcqdyn(int *mxc, int &sz) { // mcqdyn(int maxclique, int &siz)
        set_deg(V); sort(all(V), desc_deg);
        ini_col(V); rep(i, 0, sz(V) + 1) S[i].a = S[i].b = 0;
        exp_dyn(V); per(i, 0, sz(QMAX)) mxc[i] = QMAX[i];
        sz = sz(QMAX);
    }
};
