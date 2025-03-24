const int LOGN = 20;
int tin[MAXN], tout[MAXN], tmr;
int up[LOGN][MAXN];

void dfs(int v, int p) {
    tin[v] = ++tmr;

    up[0][v] = p;
    for (int i = 1; i < LOGN; i++) {
        up[i][v] = up[i - 1][up[v][i - 1]];
    }
    for(auto to : g[v]) {
        if(to != p) {
            dfs(to, v);
        }
    }
    tout[v] = tmr;
}

bool par(int a, int b) {
    if(tin[a] <= tin[b] && tout[b] <= tout[a]) return 1;
    return 0;
}

int lca(int a, int b) {
    if(par(a, b)) return a;
    if(par(b, a)) return b;
    for(int i = LOGN - 1; i >= 0; --i) if(up[a][i] && !par(up[a][i], b)) a = up[a][i];
    return up[a][0];
}