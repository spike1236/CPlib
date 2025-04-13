/*
We say that graph A includes graph B if every component of graph B is a subset of some component of graph A.

You are given two graphs, A and B. You must process queries of two types:
* add an edge to one of the graphs;
* remove an edge from one of the graphs.
After each query, you have to calculate the minimum number of edges that have to be added to A so that A includes B, and print it.
*/

int ans[MAXN];
int n, q;

struct DSU {
    veci p, s;
    int comp;
    vector<tuple<int,int,int>> h;
    DSU(int n) : p(n + 1), s(n + 1, 1), comp(n) {
        iota(all(p), 0);
    }
    int get(int a) {
        while(a != p[a]) a = p[a];
        return a;
    }
    bool unite(int a, int b) {
        a = get(a), b = get(b);
        if(a == b) return 0;
        comp--;
        if(s[a] < s[b]) swap(a,b);
        h.pb({b, p[b], s[a]});
        p[b] = a;
        s[a] += s[b];
        return 1;
    }
    int snapshot() { return sz(h); }
    void rollback(int snap) {
        while(sz(h) > snap) {
            auto [b, old_p, old_s] = h.back();
            h.pop_back();
            s[p[b]] = old_s;
            p[b] = old_p;
            comp++;
        }
    }
};
 
unique_ptr<DSU> dsuA, dsuC;
vector<tuple<char, int, int>> t[MAXN << 2];

void upd(int l, int r, tuple<char, int, int> e, int v = 1, int tl = 1, int tr = q) {
    if(l > tr || r < tl) return;
    if(l <= tl && tr <= r) {
        t[v].pb(e);
        return;
    }
    int tm = tl + tr >> 1;
    upd(l, r, e, v << 1, tl, tm);
    upd(l, r, e, v << 1 | 1, tm + 1, tr);
}
 
void build(int v = 1, int tl = 1, int tr = q) {
    int snapA = dsuA->snapshot();
    int snapC = dsuC->snapshot();
    for(auto e : t[v]) {
        dsuC->unite(get<1>(e), get<2>(e));
        if(get<0>(e) == 'A') dsuA->unite(get<1>(e), get<2>(e));
    }
    if(tl == tr) {
        ans[tl] = dsuA->comp - dsuC->comp;
    } else {
        int tm = tl + tr >> 1;
        build(v << 1, tl, tm);
        build(v << 1 | 1, tm + 1, tr);
    }
    dsuA->rollback(snapA);
    dsuC->rollback(snapC);
}
 
void solve() {
    cin >> n >> q;
    dsuA = make_unique<DSU>(n);
    dsuC = make_unique<DSU>(n);
    map<pii, int> lsA, lsB;
    for(int i = 1; i <= q; ++i) {
        char c;
        int u, v;
        cin >> c >> u >> v;
        if(u > v) swap(u, v);
        pii pr = {u, v};
        if(c == 'A') {
            if(lsA.count(pr)) {
                upd(lsA[pr], i - 1, {c, u, v});
                lsA.erase(pr);
            } else lsA[pr] = i;
        } else {
            if(lsB.count(pr)) {
                upd(lsB[pr], i - 1, {c, u, v});
                lsB.erase(pr);
            } else lsB[pr] = i;
        }
    }
    for(auto &[e, i] : lsA) {
        upd(i, q, {'A', e.first, e.second});
    }
    for(auto &[e, i] : lsB) {
        upd(i, q, {'B', e.first, e.second});
    }
    build();
    for(int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}
