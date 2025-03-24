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

    void build(const vector<T> &a) {
        for(int i = 0; i < n; ++i) t[i][0] = a[i];
        for(int j = 1; j < CNT; ++j) {
            for(int i = 0; i + (1 << j) <= PW; ++i) {
                t[j][i] = t[j - 1][i] + t[j - 1][i + (1 << (j - 1))];
            }
        }
    }

    T get(int l, int r) {
        if(l == r) return t[l][0];
        int dif = lg[l ^ r];
        int level = CNT - 1 - dif;
        T ans = t[level][l];
        if(r & ((1 << dif) - 1)) ans = ans + t[level][r];
        return ans;
    }
};
