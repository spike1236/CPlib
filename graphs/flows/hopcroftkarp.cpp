// g is adjacency list of left partition, mt is vector of -1's of the size of right partition
int HopcroftKarp(vector<veci> &g, veci &mt) {
    int n = ssize(g), res = 0;
    veci l(n, -1), q(n), d(n);
    auto dfs = [&](auto &&f, int v) -> bool {
        int t = exchange(d[v], 0) + 1;
        for(auto to : g[v]) {
            if(mt[to] == -1 || (d[mt[to]] == t && f(f, mt[to]))) {
                l[v] = to;
                mt[to] = v;
                return true;
            }
        }
        return false;
    };
    for(int t = 0, f = 0; ; t = f = 0, d.assign(n, 0)) {
        for(int i = 0; i < n; ++i) if(l[i] == -1) q[t++] = i, d[i] = 1;
        for(int i = 0; i < t; ++i) for(auto to : g[q[i]]) {
            if(mt[to] == -1) f = 1;
            else if(!d[mt[to]]) d[mt[to]] = d[q[i]] + 1, q[t++] = mt[to];
        }
        if(!f) return res;
        for(int i = 0; i < n; ++i) if(l[i] == -1) res += dfs(dfs, i);
    }
    return -1;
}