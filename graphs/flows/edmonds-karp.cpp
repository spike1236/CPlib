
int n, m;
veci g[510];
ll cap[510][510];

ll bfs(int s, int t, veci &par) {
    par.assign(n+1, 0);
    par[s] = s;
    queue<pair<int, ll>> q;
    q.push({s, 1e18});
    while(!q.empty()) {
        auto [v, f] = q.front();
        q.pop();
        for(auto to : g[v]) {
            if(!par[to] && cap[v][to]) {
                ll nf = min(f, cap[v][to]);
                par[to] = v;
                if(to == t) return nf;
                q.push({to, nf});
            }
        }
    }
    return 0;
}

void solve() {
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        g[u].push_back(v), cap[u][v] += c;
        g[v].push_back(u);
    }
    ll flow = 0, new_flow = 0;
    veci par(n+1);
    while(new_flow = bfs(1, n, par)) {
        flow += new_flow;
        int cur = n;
        while(cur != 1) {
            int prv = par[cur];
            cap[prv][cur] -= new_flow;
            cap[cur][prv] += new_flow;
            cur = prv;
        }
    }
    cout << flow;
}