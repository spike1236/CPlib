// given a tree, find the number of paths with length <= L and weight <= W

int dep[MAXN];
int sum[MAXN];
vector <pii> g[MAXN];
int used[MAXN];
int sz[MAXN];
int n, L, W;
ll ans;

void dfscalc(int v, int p) {
    sz[v] = 1;
    for(auto to : g[v]) {
        if(!used[to.f] && to.f != p) {
            dep[to.f] = dep[v] + 1;
            sum[to.f] = sum[v] + to.s;
            dfscalc(to.f, v);
            sz[v] += sz[to.f];
        }
    }
}

int centroid(int v, int p, int cn) {
    for(auto to : g[v])
        if(!used[to.f] && to.f != p && sz[to.f] > cn / 2) return centroid(to.f, v, cn);
    return v;
}

int t[MAXN];

void upd(int x, int val) {
    for(int i = x; i <= L; i |= (i + 1)) t[i] += val;
}

int get(int x) {
    int res = 0;
    for(int i = x; i >= 0; i = ((i + 1) & i) - 1) res += t[i];
    return res;
}

vector <pii> data1;

void dfs(int v, int p) {
    if(dep[v] <= L && sum[v] <= W) ++ans;
    data1.pb({sum[v], dep[v]});
    for(auto to : g[v]) if(to.f != p && !used[to.f]) dfs(to.f, v);
}

void calc(int v) {
    dep[v] = 0;
    sum[v] = 0;
    dfscalc(v, 0);
    vector <pair <pii, int> > scan;
    for(auto to : g[v]) {
        if(!used[to.f]) {
            data1.clear();
            dfs(to.f, v);
            for(auto it : data1) {
                scan.pb({{it.f, 0}, it.s});
                if(it.f <= W && it.s <= L) scan.pb({{W - it.f, 1}, L - it.s});
            }
        }
    }
    sort(all(scan));
    for(auto it : scan) {
        if(!it.f.s) upd(it.s, 1);
        else ans += get(it.s);
    }
    for(auto it : scan) if(!it.f.s) upd(it.s, -1);
    used[v] = 1;
    for(auto to : g[v]) {
        if(!used[to.f]) {
            data1.clear();
            scan.clear();
            dfs(to.f, v);
            for(auto it : data1) {
                scan.pb({{it.f, 0}, it.s});
                if(it.f <= W && it.s <= L) scan.pb({{W - it.f, 1}, L - it.s});
            }
            sort(all(scan));
            for(auto it : scan) {
                if(!it.f.s) upd(it.s, 1);
                else ans -= get(it.s);
            }
            for(auto it : scan) if(!it.f.s) upd(it.s, -1);
        }
    }
    for(auto to : g[v]) if(!used[to.f]) calc(centroid(to.f, v, sz[to.f]));
}

void solve() {
    cin >> n >> L >> W;
    for(int i = 2, v, c; i <= n; ++i) {
        cin >> v >> c;
        g[v].pb({i, c});
        g[i].pb({v, c});
    }
    dfscalc(1, 0);
    ans = 0;
    calc(centroid(1, 0, n));
    cout << ans / 2;
}