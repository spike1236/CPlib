const int LOGN = 20;
int up[LOGN][MAXN], dep[MAXN], tin[MAXN], tmr;

void dfs_precalc(int v, int p) {
    tin[v] = ++tmr;
    up[0][v] = p;
    dep[v] = dep[p] + 1;
    for (int i = 1; i < LOGN; ++i)
        up[i][v] = up[i - 1][up[i - 1][v]];
    for (auto to : g[v])
        if (to != p)
            dfs_precalc(to, v);
}

int getlca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = LOGN - 1; i >= 0; --i)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y) return x;
    for (int i = LOGN - 1; i >= 0; --i)
        if (up[i][x] != up[i][y]) {
            x = up[i][x];
            y = up[i][y];
        }
    return up[0][x];
}