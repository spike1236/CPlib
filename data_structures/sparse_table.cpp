template <typename T>
struct sptable {
    vector<vector<T>> sp;
    veci lg;
    int n, LOG;
    
    sptable(const vector<T> &a) {
        n = a.size();
        LOG = 0;
        while((1 << LOG) <= n) ++LOG;
        sp.resize(LOG, vector<T>(n + 1));
        lg.resize(n + 1);
        build(a);
    }

    void build(const vector<T> &a) {
        for(int i = 1; i <= n; ++i) sp[i][0] = a[i];
        for(int i = 2; i < MAXN; ++i) lg[i] = lg[i >> 1] + 1;
        for(int l = 1; l < LOG; ++l)
            for(int i = 1; i + (1 << l) - 1 <= n; ++i)
                sp[l][i] = __gcd(sp[l - 1][i], sp[l - 1][i + (1 << (l - 1))]);
    }
    
    T get(int l, int r) {
        int j = lg[r - l + 1];
        return __gcd(sp[j][l], sp[j][r - (1 << j) + 1]);
    }
};