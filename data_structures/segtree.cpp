template<typename T>
struct segtree {
    vector<T> t, u;
    int n;
    segtree(int n) : n(n), t(4 * n + 10), u(4 * n + 10) {}
    
    void _build(int v, int tl, int tr) {
        if(tl == tr) t[v] = a[tl];
        else {
            int tm = tl + tr >> 1;
            build(v << 1, tl, tm);
            build(v << 1 | 1, tm + 1, tr);
            t[v] = t[v << 1] + t[v << 1 | 1];
        }
    }

    void build() {
        _build(1, 1 ,n);
    }
    
    void push(int v, int tl, int tr) {
        if (u[v]) {
            int tm = tl + tr >> 1;
            t[v << 1] += u[v];
            t[v << 1 | 1] += u[v];
            u[v << 1] += u[v];
            u[v << 1 | 1] += u[v];
            u[v] = 0;
        }
    }
    
    void upd(int l, int r, T x, int v, int tl, int tr) {
        if (l <= tl && tr <= r) {
            t[v] += x;
            u[v] += x;
            return;
        }
        if (tl > r || tr < l) return;
        int tm = tl + tr >> 1;
        push(v, tl, tr);
        upd(l, r, x, v << 1, tl, tm);
        upd(l, r, x, v << 1 | 1, tm + 1, tr);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }

    void upd(int l, int r, T x) {
        upd(l, r, x, 1, 1, n);
    }
    
    T get(int l, int r, int v, int tl, int tr) {
        if (l == tl && r == tr) return t[v];
        int tm = tl + tr >> 1;
        push(v, tl, tr);
        if (r <= tm) return get(l, r, v << 1, tl, tm);
        if (l > tm) return get(l, r, v << 1 | 1, tm + 1, tr);
        return get(l, tm, v << 1, tl, tm) + get(tm + 1, r, v << 1 | 1, tm + 1, tr);
    }

    T get(int l, int r) {
        return get(l, r, 1, 1, n);
    }
};