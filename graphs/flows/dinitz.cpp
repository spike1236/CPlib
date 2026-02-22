// find max flow min cut
int n, m;
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap, long long rcap = 0) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, rcap);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
    vector<int> reachable_from(int s) {
        vector<int> vis(n);
        queue<int> q;
        vis[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : adj[u]) {
                auto e = edges[id];
                if (e.cap - e.flow > 0 && !vis[e.u]) {
                    vis[e.u] = 1;
                    q.push(e.u);
                }
            }
        }
        return vis;
    }
};

void solve() {
    cin >> n >> m;
    Dinic s(n, 0, n - 1);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        s.add_edge(u, v, 1);
        s.add_edge(v, u, 1);
    }
    cout << s.flow() << '\n';
    auto t = s.reachable_from(0);
    set<pii> st;
    for(auto x : s.edges) {
        if(t[x.u] ^ t[x.v]) st.insert({min(x.u, x.v), max(x.u, x.v)});
    }
    for(auto [x, y] : st) cout << x + 1 << ' ' << y + 1 << '\n';
}
