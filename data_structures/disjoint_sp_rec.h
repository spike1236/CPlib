template <typename T>
struct disjointsptable {
    vector<vector<T>> t;
    int n, CNT, PW;
    veci lg;

    disjointsptable(const vector<T> &a) {
        n = a.size();
        lg.resize(n + 1);
        lg[1] = 0;
        for(int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
        CNT = lg[n];
        PW = n;
        if((1 << CNT) != n) PW = (1 << (++CNT));
        t.resize(CNT, vector<T>(PW));
        build(a);
    }

    T comp(const T &x, const T &y) {
        // placeholder
        return x + y;
    }
    
    void build(const vector<T> &a, int l, int r, int isleft, int level) {
        if(isleft) {
            t[r][level] = mp(a[r], 1);
            for(int x = r - 1; x >= l; --x)
                t[x][level] = comp(mp(a[x], 1), t[x + 1][level]);
        } else {
            t[l][level] = mp(a[l], 1);
            for(int x = l + 1; x <= r; ++x)
                t[x][level] = comp(mp(a[x], 1), t[x - 1][level]);
        }
        if(l == r) return;
        int mid = l + r >> 1;
        build(a, l, mid, 1, level - 1);
        build(a, mid + 1, r, 0, level - 1);
    }
    
    T get(int l, int r) {
        int lev = lg[l ^ r];
        return comp(t[l][lev], t[r][lev]);
    }
};
